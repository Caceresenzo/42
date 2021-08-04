import { $axios } from '../utils/api'
import { DirectMessage } from '~/models'

export default class DirectMessagesAPI {
  static show(peerid: number): Promise<DirectMessage> {
    return $axios.$get(`direct-messages/${peerid}`)
  }
}
