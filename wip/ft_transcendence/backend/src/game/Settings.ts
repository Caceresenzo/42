export interface GameSettings {
  map: number;
  ballVelocity: number;
  paddleVelocity: number;
  pointToWin: number;
}

export function defaults(): GameSettings {
  return {
    map: 0,
    paddleVelocity: 3,
    ballVelocity: 3,
    pointToWin: 3,
  };
}
