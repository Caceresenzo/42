import { User } from './User'

export interface PendingGame {
  id: number
  user: User
  peer: User
}
