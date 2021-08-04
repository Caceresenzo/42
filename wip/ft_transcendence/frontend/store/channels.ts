import Vue from 'vue'
import { Action, Module, Mutation, VuexModule } from 'vuex-module-decorators'
import { Channel } from '~/models'
import { $axios } from '~/utils/api'

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'channels',
})
class ChannelsModule extends VuexModule {
  list: Array<Channel> = []

  @Mutation
  set(list: Array<Channel>) {
    this.list = list
  }

  @Mutation
  add(channel: Channel) {
    this.list.push(channel)
  }

  @Mutation
  deleteItem(channel: Channel) {
    const { id } = channel
    const index = this.list.findIndex((x) => x.id === id)

    if (index !== -1) {
      this.list.splice(index, 1)
    }
  }

  @Mutation
  update(channel: Channel) {
    const { id } = channel
    const index = this.list.findIndex((x) => x.id === id)

    if (index !== -1) {
      Vue.set(this.list, index, channel)
    }
  }

  @Action({ commit: 'set', rawError: true })
  async fetchAll() {
    const channels: Channel[] = await $axios.$get('/users/@me/channels')

    return channels
  }
}

export default ChannelsModule
