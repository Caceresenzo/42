import { User } from './User'
import { Player, Side } from './Game'

export interface Match {
  id: number
  player: { [key in Side]: Player }
  winner: User
}
