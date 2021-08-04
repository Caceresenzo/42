import { $axios } from '../utils/api'
import { Channel, ChannelUser, User } from '~/models'

export type AnUser = User | ChannelUser

export default class ChannelUsersAPI {
  static index(channel: Channel): Promise<Array<ChannelUser>> {
    return $axios.$get(`channels/${channel.id}/users`)
  }

  static show(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$get(`channels/${channel.id}/users/${user.id}`)
  }

  static create(channel: Channel, userId: number): Promise<ChannelUser> {
    return $axios.$post(`channels/${channel.id}/users`, {
      userId,
    })
  }

  static promote(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$post(`channels/${channel.id}/users/${user.id}/admin`)
  }

  static demote(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$delete(`channels/${channel.id}/users/${user.id}/admin`)
  }

  static ban(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$post(`channels/${channel.id}/users/${user.id}/ban`)
  }

  static unban(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$delete(`channels/${channel.id}/users/${user.id}/ban`)
  }

  static mute(
    channel: Channel,
    user: AnUser,
    duration: number | null
  ): Promise<ChannelUser> {
    return $axios.$post(`channels/${channel.id}/users/${user.id}/mute`, {
      duration,
    })
  }

  static unmute(channel: Channel, user: AnUser): Promise<ChannelUser> {
    return $axios.$delete(`channels/${channel.id}/users/${user.id}/mute`)
  }

  static transfer(channel: Channel, user: ChannelUser): Promise<ChannelUser> {
    return $axios.$post(`channels/${channel.id}/users/${user.id}/transfer`)
  }

  static destroy(channel: Channel, user: AnUser): Promise<void> {
    return $axios.$delete(`channels/${channel.id}/users/${user.id}`)
  }
}
