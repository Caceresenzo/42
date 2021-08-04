<template>
  <v-list>
    <v-card-text v-if="!withHidden.length" class="text-center">
      <template v-if="filter"> no result with filter `{{ filter }}` </template>
      <template v-else> no user available </template>
    </v-card-text>
    <user-item v-for="user in withHidden" :key="user.id" :user="user" />
    <v-card-text v-if="hiddenCount" class="text-center text--secondary">
      hiding {{ hiddenCount }} user(s)
    </v-card-text>
  </v-list>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { relationshipsStore, socketStore } from '~/store'

@Component
export default class List extends Vue {
  @Prop()
  users!: User[]

  @Prop()
  filter!: string

  @Prop()
  hideBlocked!: boolean

  @Prop()
  hideBanned!: boolean

  get filtered() {
    const { filter } = this

    if (!filter?.length) {
      return this.users
    }

    return this.users.filter((x) => x.username.includes(filter))
  }

  get withHidden() {
    const { blockedPeerIds } = relationshipsStore
    const { connectedUserIds } = socketStore

    let list = this.filtered

    if (this.hideBlocked) {
      list = list.filter((x) => !blockedPeerIds.includes(x.id))
    }

    if (this.hideBanned) {
      list = list.filter((x) => !x.banned)
    }

    return list.sort(({ id: a }, { id: b }) => {
      const first = +connectedUserIds.includes(a)
      const second = +connectedUserIds.includes(b)

      return second - first
    })
  }

  get hiddenCount() {
    return this.filtered.length - this.withHidden.length
  }
}
</script>
