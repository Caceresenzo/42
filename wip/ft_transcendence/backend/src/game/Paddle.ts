import { PADDLE_HEIGHT, PADDLE_WIDTH } from "./Constants";
import { Rectangle } from "./Shape";

export class Paddle extends Rectangle {
  constructor(x: number, y: number) {
    super(x, y, PADDLE_WIDTH, PADDLE_HEIGHT);
  }

  toMiddleOf(height: number) {
    this.y = height / 2 - this.height / 2;
  }
}
