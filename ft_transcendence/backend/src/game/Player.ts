import { Socket } from "socket.io";
import User from "../entities/User";

export class Player {
  public readonly user: User;
  public score: number = 0;

  constructor(public socket: Socket) {
    this.user = socket.data.user;
  }

  setDisconnected() {
    this.socket = null;
  }

  setConnected(socket: Socket) {
    this.socket = socket;
  }

  get connected(): boolean {
    return this.socket != null;
  }

  public toJSON(): any {
    return {
      user: this.user,
      score: this.score,
      connected: this.connected,
    };
  }
}
