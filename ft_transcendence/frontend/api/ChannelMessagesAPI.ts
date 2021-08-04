import { $axios } from '../utils/api'
import { Channel, ChannelMessage, ChannelMessageContentType } from '~/models'

export interface ChannelMessageCreateRequest {
  type: ChannelMessageContentType
  content: string
}

export default class ChannelMessagesAPI {
  static index(channel: Channel): Promise<Array<ChannelMessage>> {
    return $axios.$get(`channels/${channel.id}/messages`)
  }

  static show(
    channel: Channel,
    message: ChannelMessage
  ): Promise<ChannelMessage> {
    return $axios.$get(`channels/${channel.id}/users/${message.id}`)
  }

  static create(
    channel: Channel,
    body: ChannelMessageCreateRequest
  ): Promise<ChannelMessage> {
    return $axios.$post(`channels/${channel.id}/messages`, body)
  }

  static destroy(channel: Channel, message: ChannelMessage): Promise<void> {
    return $axios.$delete(`channels/${channel.id}/users/${message.id}`)
  }
}
