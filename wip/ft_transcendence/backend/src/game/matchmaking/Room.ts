import { Socket } from "socket.io";

export default class Room {
  private awaitings: Array<Socket>;

  constructor(public readonly id: number) {
    this.awaitings = [];
  }

  public accept(socket: Socket): boolean {
    throw new Error("not implemented");
  }

  protected add(socket: Socket): void {
    if (this.contains(socket)) {
      return;
    }

    this.awaitings.push(socket);
  }

  public remove(socket: Socket): void {
    const index = this.awaitings.findIndex((x) => x.id === socket.id);
    if (index !== -1) {
      this.awaitings.splice(index, 1);
    }
  }

  protected contains(socket: Socket) {
    const { id } = socket;

    return !!this.awaitings.find((x) => x.id === id);
  }

  public pop1(): Socket {
    return this.awaitings.shift();
  }

  public pop2(): [Socket, Socket] {
    return [this.awaitings.shift(), this.awaitings.shift()];
  }

  public size(): number {
    return this.awaitings.length;
  }

  public isEmpty(): boolean {
    return this.awaitings.length === 0;
  }
}
