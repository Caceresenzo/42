import { Socket } from "socket.io";
import { Inject, Service } from "typedi";
import config from "../config";
import PendingGame from "../entities/PendingGame";
import User from "../entities/User";
import Game from "../game/Game";
import Gatekeeper from "../game/matchmaking/Gatekeeper";
import Room from "../game/matchmaking/Room";
import GameService from "./GameService";

@Service()
export default class MatchMakingService {
  private gatekeeper = new Gatekeeper();

  constructor(
    @Inject()
    private gameService: GameService
  ) {}

  public async add(socket: Socket, pendingGame?: PendingGame): Promise<Game> {
    const user: User = socket.data.user;
    if (this.gameService.findByUser(user)) {
      throw new Error("already in game");
    }

    const room = this.gatekeeper.add(socket, pendingGame);
    if (!room) {
      return null;
    }

    const sockets = this.popSockets(room);
    if (!sockets) {
      return null;
    }

    this.destroyIfEmpty(room);

    return this.gameService.start(...sockets, pendingGame);
  }

  public remove(socket: Socket): void {
    const room = this.gatekeeper.remove(socket);

    this.destroyIfEmpty(room);
  }

  private popSockets(room: Room): [Socket, Socket] {
    if (config.MATCHMAKING_ONLY_ONE) {
      if (room.size() < 1) {
        return null;
      }

      const first = this.gatekeeper.pop1(room);
      return [first, first];
    } else {
      if (room.size() < 2) {
        return null;
      }

      return this.gatekeeper.pop2(room);
    }
  }

  private destroyIfEmpty(room: Room | null): void {
    if (room?.isEmpty()) {
      this.gatekeeper.destroyRoom(room);
    }
  }
}
