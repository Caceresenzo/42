import { Channel } from './Channel'
import { User } from './User'

export interface DirectMessage {
  channel: Channel
  peer: User
}
