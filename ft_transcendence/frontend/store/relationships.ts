import Vue from 'vue'
import { Action, Module, Mutation, VuexModule } from 'vuex-module-decorators'
import { Relationship, RelationshipType, User } from '~/models'
import { $axios } from '~/utils/api'

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'relationships',
})
class RelationshipsModule extends VuexModule {
  list: Array<Relationship> = []

  @Mutation
  set(list: Array<Relationship>) {
    this.list = list
  }

  @Mutation
  updateItem(relationship?: Relationship) {
    if (!relationship) {
      return
    }

    const {
      peer: { id },
    } = relationship
    const index = this.list.findIndex((x) => x.peer.id === id)

    if (index !== -1) {
      Vue.set(this.list, index, relationship)
    } else {
      this.list.push(relationship)
    }
  }

  @Mutation
  deleteItem(user: User) {
    const { id } = user
    const index = this.list.findIndex((x) => x.peer.id === id)

    if (index !== -1) {
      this.list.splice(index, 1)
    }
  }

  get blocked(): Array<Relationship> {
    return this.list.filter((x) => x.type === RelationshipType.BLOCK)
  }

  get blockedPeerIds() {
    return this.blocked.map((x) => x.peer.id)
  }

  get friends(): Array<Relationship> {
    return this.list.filter((x) => x.type === RelationshipType.FRIEND)
  }

  get friendPeerIds(): Array<number> {
    return this.friends.map((x) => x.peer.id)
  }

  @Action({ commit: 'set', rawError: true })
  async fetchAll() {
    const relationships: Relationship[] = await $axios.$get(
      '/users/@me/relationships'
    )

    return relationships
  }

  private findIndex(user: User) {
    const { id } = user

    return this.list.findIndex((x) => x.peer.id === id)
  }
}

export default RelationshipsModule
