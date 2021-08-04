import { Socket } from "socket.io";
import User from "../../entities/User";
import Room from "./Room";

export default class PrivateRoom extends Room {
  constructor(id: number, private readonly users: Array<User>) {
    super(id);
  }

  public accept(socket: Socket) {
    const id: number = socket.data.user.id;

    if (!this.users.find((x) => x.id === id)) {
      return false;
    }

    this.add(socket);

    return true;
  }
}
