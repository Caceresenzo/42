import { Rectangle } from "./Shape";

let incrementalId = 0;

export class Map {
  public readonly id: number;

  constructor(public name: string, public obstacles: Array<Rectangle>) {
    this.id = ++incrementalId;
  }
}
