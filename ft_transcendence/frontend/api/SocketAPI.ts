import { $socket } from '~/utils/api'
import { Channel } from '~/models'

export default class SocketAPI {
  static channelConnect(channel: Channel): Promise<void> {
    return new Promise((resolve, reject) => {
      $socket.emit(
        'channel_connect',
        {
          channelId: channel.id,
        },
        (error: any, message: any) => {
          if (error) {
            reject(error)
          } else {
            resolve(message)
          }
        }
      )
    })
  }
}
