import { Module, VuexModule, Action, Mutation } from 'vuex-module-decorators'
import { DirectMessage } from '~/models/DirectMessage'
import { $axios } from '~/utils/api'

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'directMessages',
})
class DirectMessageModule extends VuexModule {
  list: Array<DirectMessage> = []

  @Mutation
  set(list: Array<DirectMessage>) {
    this.list = list
  }

  @Action({ commit: 'set', rawError: true })
  async fetchAll() {
    const directMessages = await $axios.$get('/users/@me/direct-messages')

    return directMessages
  }
}

export default DirectMessageModule
