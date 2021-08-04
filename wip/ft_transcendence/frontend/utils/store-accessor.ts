/* eslint-disable import/no-mutable-exports */
import { Store } from 'vuex'
import { getModule } from 'vuex-module-decorators'
import AchievementsModule from '~/store/achievements'
import AuthModule from '~/store/auth'
import ChannelsModule from '~/store/channels'
import DirectMessageModule from '~/store/directMessages'
import RelationshipsModule from '~/store/relationships'
import SocketModule from '~/store/socket'
import UIModule from '~/store/ui'

let uiStore: UIModule
let authStore: AuthModule
let achievementsStore: AchievementsModule
let directMessageStore: DirectMessageModule
let socketStore: SocketModule
let channelsStore: ChannelsModule
let relationshipsStore: RelationshipsModule

function initializeStores(store: Store<any>): void {
  uiStore = getModule(UIModule, store)
  authStore = getModule(AuthModule, store)
  directMessageStore = getModule(DirectMessageModule, store)
  achievementsStore = getModule(AchievementsModule, store)
  socketStore = getModule(SocketModule, store)
  channelsStore = getModule(ChannelsModule, store)
  relationshipsStore = getModule(RelationshipsModule, store)
}

export {
  initializeStores,
  uiStore,
  achievementsStore,
  directMessageStore,
  authStore,
  socketStore,
  channelsStore,
  relationshipsStore,
}
