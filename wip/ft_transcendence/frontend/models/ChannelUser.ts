export interface ChannelUser {
  id: number
  username: string
  admin: boolean
  banned: boolean
  muted: boolean
  mutedUntil: Date
}
