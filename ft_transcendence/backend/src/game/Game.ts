import * as socketio from "socket.io";
import { Container } from "typedi";
import Match from "../entities/Match";
import PendingGame from "../entities/PendingGame";
import User from "../entities/User";
import AchievementProgressService from "../services/AchievementProgressService";
import ChannelMessageService from "../services/ChannelMessageService";
import GameService from "../services/GameService";
import MatchService from "../services/MatchService";
import UserStatisticsService from "../services/UserStatisticsService";
import Achievements from "./Achievements";
import { Ball } from "./Ball";
import { COLLISION_STEP, HEIGHT, INITIAL_PADDLE_Y, PADDLE_HEIGHT, WIDTH } from "./Constants";
import { Direction, Side } from "./Enums";
import { Map } from "./Map";
import Maps from "./Maps";
import { Paddle } from "./Paddle";
import { Player } from "./Player";
import { defaults as defaultsGameSettings, GameSettings } from "./Settings";
import { CollisionResult, Rectangle } from "./Shape";
import { World } from "./World";

function sleep(ms: number) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

export default class Game {
  public id: number | null = null;

  private interval?: ReturnType<typeof setInterval>;

  private ball: Ball = new Ball(0, 0, 3.5, 1.5);
  private direction: Direction;

  private paddle = {
    [Side.LEFT]: new Paddle(15, INITIAL_PADDLE_Y),
    [Side.RIGHT]: new Paddle(770, INITIAL_PADDLE_Y),
  };

  private player = {
    [Side.LEFT]: null as Player,
    [Side.RIGHT]: null as Player,
  };

  private world = new World();
  private map: Map;

  public countdown: number = 3;
  public settings: GameSettings;

  public matchService = Container.get(MatchService);
  public userStatisticsService = Container.get(UserStatisticsService);
  public achievementProgressService = Container.get(AchievementProgressService);
  public gameService = Container.get(GameService);
  public channelMessageService = Container.get(ChannelMessageService);

  constructor(
    first: socketio.Socket,
    second: socketio.Socket,
    private pendingGame?: PendingGame
  ) {
    this.settings = pendingGame?.settings || defaultsGameSettings();
    this.map = Maps.find(this.settings.map);

    this.player[Side.LEFT] = new Player(first);
    this.player[Side.RIGHT] = new Player(second);

    this.direction = this.nextDirection();
    this.ball.setDirection(this.direction);

    this.paddle[Side.LEFT].toMiddleOf(HEIGHT);
    this.paddle[Side.RIGHT].toMiddleOf(HEIGHT);

    this.repositionBall();
  }

  start() {
    for (const player of this.players) {
      player.socket.emit("game_connect", this.toJSON());
    }

    if (this.interval === undefined) {
      this.interval = setInterval(() => this.loop(), 1000 / 20);
    }

    this.decount();
  }

  repositionBall() {
    this.ball.x = WIDTH / 2;
    this.ball.y = HEIGHT / 2;
  }

  restart() {
    this.repositionBall();

    this.direction = this.nextDirection();
    this.ball.setDirection(this.direction);
    this.countdown = 3;

    this.interval = setInterval(() => this.loop(), 1000 / 20);
    this.decount();
  }

  private nextDirection() {
    return Math.random() >= 0.5 ? Direction.LEFT : Direction.RIGHT;
  }

  stop() {
    if (this.interval != undefined) {
      clearInterval(this.interval);
      this.interval = undefined;
    }
  }

  handleBallCollision(rectanble: Rectangle, nextDirection: Direction) {
    const result = rectanble.collide(this.ball);

    if (
      result === CollisionResult.HORIZONTAL ||
      result === CollisionResult.BOTH
    ) {
      this.ball.yVelocity *= -1;
    }

    if (
      result === CollisionResult.VERTICAL ||
      result === CollisionResult.BOTH
    ) {
      this.ball.xVelocity *= -1;

      this.direction = nextDirection;

      // console.log(
      //   {
      //     [CollisionResult.NONE]: "none",
      //     [CollisionResult.HORIZONTAL]: "hor",
      //     [CollisionResult.VERTICAL]: "ver",
      //     [CollisionResult.BOTH]: "both",
      //   }[result]
      // );
    }
  }

  updateBall() {
    for (let i = 0; i < COLLISION_STEP; i++) {
      if (this.world.collideX(this.ball)) {
        return 0;
      }

      if (this.world.collideY(this.ball)) {
        this.ball.yVelocity *= -1;
      }

      if (this.direction == Direction.RIGHT) {
        this.handleBallCollision(this.paddle[Side.RIGHT], Direction.LEFT);
      }

      if (this.direction == Direction.LEFT) {
        this.handleBallCollision(this.paddle[Side.LEFT], Direction.RIGHT);
      }

      for (const obstacle of this.map.obstacles) {
        this.handleBallCollision(
          obstacle,
          this.direction == Direction.LEFT ? Direction.RIGHT : Direction.LEFT
        );
      }

      this.ball.applyVelocity(this.settings.ballVelocity / COLLISION_STEP);
    }

    return 1;
  }

  async stopGame(winner: Player) {
    this.stop();

    const io = Container.get(socketio.Server);

    let match = new Match();
    match.player1 = this.player[Side.LEFT].user;
    match.player2 = this.player[Side.RIGHT].user;
    match.score1 = this.player[Side.LEFT].score;
    match.score2 = this.player[Side.RIGHT].score;
    match.winner = winner.user;
    await this.matchService.save(match);

    if (match.id && this.pendingGame) {
      const message = await this.channelMessageService.findById(
        (
          await this.pendingGame.message
        )?.id
      );

      if (message) {
        const channel = await message.channel;

        message.channel = Promise.resolve(channel); /* just in case */
        message.content = JSON.stringify({
          id: this.pendingGame.id,
          state: "played",
          matchId: match.id,
        });

        await this.channelMessageService.edit(message);
      }
    }

    if (winner == this.player[Side.LEFT]) {
      await this.userStatisticsService.incrementWinCount(
        this.player[Side.LEFT].user
      );
      await this.userStatisticsService.incrementWinCount(
        this.player[Side.LEFT].user
      );
    } else {
      await this.userStatisticsService.incrementWinCount(
        this.player[Side.RIGHT].user
      );
      await this.userStatisticsService.incrementLossCount(
        this.player[Side.LEFT].user
      );
    }

    io.to(this.toRoom()).emit("game_end", match);

    try {
      await this.achievementProgressService.increment(
        Achievements.FIRST_TIME,
        winner.user
      );
      await this.achievementProgressService.increment(
        Achievements.KING_OF_THE_HILL,
        winner.user
      );
      await this.achievementProgressService.increment(
        Achievements.AT_WHAT_COST,
        winner.user
      );

      for (const user of this.users) {
        await this.achievementProgressService.increment(
          Achievements.BEGINNER,
          user
        );
        await this.achievementProgressService.increment(
          Achievements.INTERMEDIATE,
          user
        );
        await this.achievementProgressService.increment(
          Achievements.GAMER,
          user
        );
        await this.achievementProgressService.increment(
          Achievements.GO_OUTSIDE,
          user
        );
      }
    } catch (error) {
      console.log(error);
    }

    this.gameService.delete(this);
  }

  loop() {
    const io = Container.get(socketio.Server);

    if (this.countdown === -1 && this.updateBall() === 0) {
      clearInterval(this.interval);

      let scorer: Player;
      if (this.direction == Direction.LEFT) {
        scorer = this.player[Side.RIGHT];
      } else {
        scorer = this.player[Side.LEFT];
      }

      scorer.score++;

      if (scorer.score === this.settings.pointToWin) {
        this.stopGame(scorer);
        return;
      }

      io.to(this.toRoom()).emit("game_scored", {
        ...this.toJSON(),
        scorer,
      });

      clearInterval(this.interval);

      setTimeout(() => this.restart(), 1000);
    }

    io.to(this.toRoom()).emit("game_state", this.toJSON());
  }

  async decount() {
    while (this.countdown != -1) {
      await sleep(800);
      this.countdown--;
    }
  }

  movePaddle(user: User, y: number) {
    if (y < 0 || y > HEIGHT - PADDLE_HEIGHT) {
      return false;
    }

    if (user.id == this.player[Side.LEFT].user.id) {
      this.paddle[Side.LEFT].y = y;
    }

    if (user.id == this.player[Side.RIGHT].user.id) {
      this.paddle[Side.RIGHT].y = y;
    }

    return true;
  }

  get players(): [Player, Player] {
    return [this.player[Side.LEFT], this.player[Side.RIGHT]];
  }

  get users(): [User, User] {
    return [this.player[Side.LEFT].user, this.player[Side.RIGHT].user];
  }

  public toJSON() {
    return {
      id: this.id,
      player: this.player,
      paddle: this.paddle,
      ball: this.ball,
      countdown: this.countdown,
      map: this.map,
      factor: this.settings.paddleVelocity,
      settings: this.settings,
    };
  }

  public toRoom(): string {
    return `game_${this.id}`;
  }
}
