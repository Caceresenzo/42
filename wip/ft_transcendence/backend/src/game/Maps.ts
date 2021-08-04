import { HEIGHT, WIDTH } from "./Constants";
import { Map } from "./Map";
import { Rectangle } from "./Shape";

const tenthWidth = WIDTH / 10;
const tenthHeight = HEIGHT / 10;

export default class Maps {
  static find(id: number): Map {
    return Maps.pool.find((x) => x.id === id) || Maps.pool[0];
  }

  static readonly pool: Array<Map> = [
    new Map("Normal", []),
    new Map("Pause", [
      new Rectangle(
        tenthWidth * 3,
        tenthHeight * 2,
        tenthWidth,
        tenthHeight * 5
      ),
      new Rectangle(
        tenthWidth * 6,
        tenthHeight * 2,
        tenthWidth,
        tenthHeight * 5
      ),
    ]),
    new Map("Pipe", [
      new Rectangle(
        tenthWidth * 2,
        tenthHeight * 3,
        tenthWidth * 6,
        tenthHeight
      ),
      new Rectangle(
        tenthWidth * 2,
        tenthHeight * 6,
        tenthWidth * 6,
        tenthHeight
      ),
    ]),
    new Map("Square", [
      new Rectangle(
        tenthWidth * 2,
        tenthHeight * 2,
        tenthWidth,
        tenthHeight * 2
      ),
      new Rectangle(
        tenthWidth * 6,
        tenthHeight * 2,
        tenthWidth,
        tenthHeight * 2
      ),
      new Rectangle(
        tenthWidth * 3,
        tenthHeight * 6,
        tenthWidth,
        tenthHeight * 2
      ),
      new Rectangle(
        tenthWidth * 7,
        tenthHeight * 6,
        tenthWidth,
        tenthHeight * 2
      ),
    ]),
  ];
}
