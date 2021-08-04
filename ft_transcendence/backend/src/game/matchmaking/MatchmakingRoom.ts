import { Socket } from "socket.io";
import Room from "./Room";

export default class MatchmakingRoom extends Room {
  constructor(id: number) {
    super(id);
  }

  public accept(socket: Socket) {
    this.add(socket);

    return true;
  }
}
