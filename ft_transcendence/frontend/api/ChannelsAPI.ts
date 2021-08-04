import { $axios } from '../utils/api'
import { Channel, ChannelVisibility } from '~/models'

export interface ChannelCreateRequest {
  name: string
  visibility: ChannelVisibility
  password?: string
}

export type ChannelUpdateRequest = ChannelCreateRequest

export default class ChannelsAPI {
  static index(): Promise<Array<Channel>> {
    return $axios.$get(`channels`)
  }

  static show(id: number): Promise<Channel> {
    return $axios.$get(`channels/${id}`)
  }

  static create(body: ChannelCreateRequest): Promise<Channel> {
    return $axios.$post(`channels`, body)
  }

  static update(
    channel: Channel,
    body: ChannelUpdateRequest
  ): Promise<Channel> {
    return $axios.$post(`channels/${channel.id}`, body)
  }

  static destroy(channel: Channel): Promise<void> {
    return $axios.$delete(`channels/${channel.id}`)
  }

  static unlock(channel: Channel, password: string | null): Promise<Channel> {
    return $axios.$post(`users/@me/channels`, {
      channelId: channel.id,
      password: password?.length ? password : undefined,
    })
  }
}
