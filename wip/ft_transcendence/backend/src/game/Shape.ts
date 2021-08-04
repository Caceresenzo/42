export class Shape {
  constructor(public x: number, public y: number) {}
}

export class Circle extends Shape {
  constructor(x: number, y: number, public radius: number) {
    super(x, y);
  }

  get radiusSquare() {
    return Math.pow(this.radius, 2);
  }
}

export enum CollisionResult {
  NONE = 0,
  VERTICAL,
  HORIZONTAL,
  BOTH,
}

export class Rectangle extends Shape {
  constructor(
    x: number,
    y: number,
    public width: number,
    public height: number
  ) {
    super(x, y);
  }

  // http://www.jeffreythompson.org/collision-detection/circle-rect.php
  // https://stackoverflow.com/a/62586006/7292958
  collide(circle: Circle): CollisionResult {
    const { x: cx, y: cy, radius } = circle;
    const { x: rx, y: ry, width: rw, height: rh } = this;

    let testX = cx;
    let testY = cy;

    // which edge is closest?
    if (cx < rx) testX = rx;
    // compare to left edge
    else if (cx > rx + rw) testX = rx + rw; // right edge
    if (cy < ry) testY = ry;
    // top edge
    else if (cy > ry + rh) testY = ry + rh; // bottom edge

    // get distance from closest edges
    const distX = Math.abs(cx - testX);
    const distY = Math.abs(cy - testY);

    // const distX = Math.abs(cx - rx) - rw / 2;
    // const distY = Math.abs(cx - ry) - rh / 2;

    if (distX > radius || distY > radius) {
      return CollisionResult.NONE;
    }

    if (distX <= 0) {
      return CollisionResult.HORIZONTAL;
    }

    if (distY <= 0) {
      return CollisionResult.VERTICAL;
    }

    const distance = Math.sqrt(distX * distX + distY * distY);

    // if the distance is less than the radius, collision!
    if (distance <= radius) {
      return CollisionResult.BOTH;
    }

    return CollisionResult.NONE;
  }
}
