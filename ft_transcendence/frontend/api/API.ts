import AchievementsAPI from './AchievementsAPI'
import ChannelMessagesAPI from './ChannelMessagesAPI'
import ChannelsAPI from './ChannelsAPI'
import ChannelUsersAPI from './ChannelUsersAPI'
import DirectMessagesAPI from './DirectMessagesAPI'
import SearchAPI from './SearchAPI'
import SocketAPI from './SocketAPI'
import UsersAPI from './UsersAPI'

export default class API {
  static Achievements = AchievementsAPI
  static Users = UsersAPI
  static Channels = ChannelsAPI
  static ChannelMessages = ChannelMessagesAPI
  static ChannelUsers = ChannelUsersAPI
  static DirectMessages = DirectMessagesAPI
  static Search = SearchAPI
  static Socket = SocketAPI
}
