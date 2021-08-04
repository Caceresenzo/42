import { Direction } from "./Enums";
import { Circle } from "./Shape";

export class Ball extends Circle {
  constructor(
    x: number,
    y: number,
    public xVelocity: number,
    public yVelocity: number
  ) {
    super(x, y, 15);
  }

  applyVelocity(multiplier: number) {
    this.x += this.xVelocity * multiplier;
    this.y += this.yVelocity * multiplier;
  }

  setDirection(direction: Direction) {
    if (direction === Direction.LEFT && this.xVelocity > 0) {
      this.xVelocity *= -1;
    }

    if (direction === Direction.RIGHT && this.xVelocity < 0) {
      this.xVelocity *= -1;
    }
  }
}
