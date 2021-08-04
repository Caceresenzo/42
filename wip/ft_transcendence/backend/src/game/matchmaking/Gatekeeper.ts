import { Socket } from "socket.io";
import PendingGame from "../../entities/PendingGame";
import User from "../../entities/User";
import MatchmakingRoom from "./MatchmakingRoom";
import PrivateRoom from "./PrivateRoom";
import Room from "./Room";

export default class Gatekeeper {
  private readonly roomByUser: { [key: number]: Room };
  private readonly rooms: { [key: number]: Room };

  constructor() {
    this.roomByUser = {};
    this.rooms = {};
  }

  public add(socket: Socket, pendingGame?: PendingGame): Room {
    const user: User = socket.data.user;

    if (this.getRoomOfUser(user)) {
      throw new Error("already in room");
    }

    const room = this.getRoom(pendingGame);

    if (room.accept(socket)) {
      this.roomByUser[user.id] = room;

      return room;
    }

    if (room.isEmpty()) {
      this.destroyRoom(room);
    }

    return null;
  }

  public pop1(room: Room): Socket {
    const a = room.pop1();

    this.remove(a);

    return a;
  }

  public pop2(room: Room): [Socket, Socket] {
    const [a, b] = room.pop2();

    this.remove(a);
    this.remove(b);

    return [a, b];
  }

  public destroyRoom(room: Room) {
    delete this.rooms[room.id];
  }

  public remove(socket: Socket): Room | null {
    const user: User = socket.data.user;
    const room = this.getRoomOfUser(user);

    if (room) {
      room.remove(socket);

      delete this.roomByUser[user.id];

      return room;
    }

    return null;
  }

  private getRoomOfUser(user: User): Room | null {
    return this.roomByUser[user.id] || null;
  }

  private getRoom(pendingGame?: PendingGame): Room {
    const id = pendingGame?.id || 0;

    const room = this.rooms[id];
    if (room) {
      return room;
    }

    return (this.rooms[id] = this.createRoom(id, pendingGame));
  }

  private createRoom(id: number, pendingGame?: PendingGame): Room {
    if (pendingGame) {
      return new PrivateRoom(id, [pendingGame.user, pendingGame.peer]);
    }

    return new MatchmakingRoom(id);
  }
}
