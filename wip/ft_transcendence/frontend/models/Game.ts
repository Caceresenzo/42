import { User } from './User'

export enum Side {
  LEFT,
  RIGHT,
}

export interface Player {
  user: User
  score: number
  connected: boolean
}

export interface Rectangle {
  x: number
  y: number
  width: number
  height: number
}

export interface Map {
  name: string
  obstacles: Array<Rectangle>
}

export interface Settings {
  map: number
  ballVelocity: number
  paddleVelocity: number
  pointToWin: number
}

export interface Game {
  id: number
  player: {
    [key in Side]: Player
  }
  paddle: {
    [key in Side]: Rectangle
  }
  ball: {
    x: number
    y: number
    radius: number
  }
  countdown: number
  sprite: any
  factor: any
  winner?: Player
  scorer?: Player
  map: Map
  settings: Settings
}
