import { Ball } from "./Ball";
import { HEIGHT, WALL_THICKNESS, WIDTH } from "./Constants";
import { Side } from "./Enums";
import { CollisionResult, Rectangle } from "./Shape";

enum WallSide {
  TOP,
  BOTTOM,
  LEFT,
  RIGHT,
}

const walls = {
  [WallSide.TOP]: new Rectangle(
    -WALL_THICKNESS,
    -WALL_THICKNESS,
    WIDTH + WALL_THICKNESS * 2,
    WALL_THICKNESS
  ),
  [WallSide.BOTTOM]: new Rectangle(
    -WALL_THICKNESS,
    HEIGHT,
    WIDTH + WALL_THICKNESS * 2,
    WALL_THICKNESS
  ),
  [WallSide.LEFT]: new Rectangle(
    -WALL_THICKNESS,
    -WALL_THICKNESS,
    WALL_THICKNESS,
    HEIGHT + WALL_THICKNESS * 2
  ),
  [WallSide.RIGHT]: new Rectangle(
    WIDTH,
    -WALL_THICKNESS,
    WALL_THICKNESS,
    HEIGHT + WALL_THICKNESS * 2
  ),
};

export class World {
  constructor() {}

  collideX(circle: Ball) {
    return (
      walls[WallSide.LEFT].collide(circle) !== CollisionResult.NONE ||
      walls[WallSide.RIGHT].collide(circle) !== CollisionResult.NONE
    );
  }

  collideY(circle: Ball) {
    return (
      walls[WallSide.TOP].collide(circle) !== CollisionResult.NONE ||
      walls[WallSide.BOTTOM].collide(circle) !== CollisionResult.NONE
    );
  }
}
