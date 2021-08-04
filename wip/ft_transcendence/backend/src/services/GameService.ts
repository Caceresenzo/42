import { Socket } from "socket.io";
import { Inject, Service } from "typedi";
import PendingGame from "../entities/PendingGame";
import User from "../entities/User";
import Game from "../game/Game";
import SocketService from "./SocketService";

@Service()
export default class GameService {
  private repository: { [key: string]: Game } = {};
  private players: { [key: number]: Game } = {};

  constructor(
    @Inject()
    private readonly socketService: SocketService
  ) {}

  private incrementalId = 0;

  public findByUser(user: User) {
    return this.players[user.id];
  }

  public start(first: Socket, second: Socket, pendingGame?: PendingGame): Game {
    const game = new Game(first, second, pendingGame);
    this.provideId(game);

    this.save(game);

    game.start();

    this.socketService.broadcastGameStarting(game);

    return game;
  }

  public findById(id: number) {
    return this.repository[id];
  }

  public save(game: Game): Game {
    if (!game.id) {
      this.provideId(game);
    }

    this.repository[game.id] = game;
    for (const player of game.players) {
      this.socketService.playingUsers.onJoin(player.socket);
      this.players[player.user.id] = game;
    }

    return game;
  }

  public delete(game: Game): void {
    if (!game.id) {
      throw new Error("cannot delete game without an id");
    }

    delete this.repository[game.id];

    for (const player of game.players) {
      this.socketService.playingUsers.onUserQuit(player.user);
      delete this.players[player.user.id];
    }
  }

  private provideId(game: Game): void {
    if (game.id) {
      throw new Error("game already have an id");
    }

    game.id = ++this.incrementalId;
  }

  public gameMove(gameId: number, player: User, newY: number) {
    const game = this.findById(gameId);

    if (!game) {
      return false;
    }

    return game.movePaddle(player, newY);
  }

  public onConnected(socket: Socket) {
    const user: User = socket.data.user;
    const game = this.findByUser(user);

    if (!game) {
      return;
    }

    const player = game.players.filter((x) => x.user.is(user));
    for (const instance of player) {
      if (!instance.connected) {
        instance.setConnected(socket);
      }
    }
  }

  public onDisconnected(socket: Socket) {
    const user: User = socket.data.user;
    const game = this.findByUser(user);

    if (!game) {
      return;
    }

    const player = game.players.filter((x) => x.socket?.id === socket.id);
    for (const instance of player) {
      instance.setDisconnected();
    }
  }
}
