import { User } from './User'
import { Channel } from './Channel'

export enum ChannelMessageContentType {
  TEXT = 'text',
  INVITE = 'invite',
}

export interface ChannelMessage {
  id: number
  type: ChannelMessageContentType
  content: string
  user: User
  channel: Channel
  createdAt: Date
}
