import { User } from './User'
import { ChannelUser } from './ChannelUser'

export enum ChannelVisibility {
  PUBLIC = 'public',
  PRIVATE = 'private',
  PROTECTED = 'protected',
}

export enum ChannelType {
  GROUP = 'group',
  PRIVATE = 'private',
}

export interface Channel {
  id: number
  name: string
  owner: User
  visibility: ChannelVisibility
  users: ChannelUser[]
}
