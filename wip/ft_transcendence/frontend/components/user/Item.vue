<template>
  <v-list-item link :to="to">
    <v-list-item-avatar size="60">
      <user-avatar :user="user" />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-list-item-title>
        {{ user.username }}
        <icon-tooltip
          v-if="user.admin"
          icon="mdi-account-supervisor"
          icon-right
          top
          text="Administrator"
        />
        <icon-tooltip
          v-if="friend"
          icon="mdi-account-heart"
          icon-right
          top
          text="Friend"
        />
        <icon-tooltip
          v-if="playing"
          icon="mdi-controller-classic"
          icon-right
          top
          text="Playing"
        />
        <icon-tooltip
          v-if="blocked"
          icon="mdi-account-remove"
          icon-right
          top
          text="Blocked"
        />
        <icon-tooltip
          v-if="user.banned"
          icon="mdi-cancel"
          icon-right
          top
          text="Banned"
        />
      </v-list-item-title>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { relationshipsStore, socketStore } from '~/store'

@Component
export default class Item extends Vue {
  @Prop()
  user!: User

  get to() {
    return `/users/${this.user.id}`
  }

  get playing(): boolean {
    return socketStore.playingUserIds.includes(this.user.id)
  }

  get blocked(): boolean {
    return relationshipsStore.blockedPeerIds.includes(this.user.id)
  }

  get friend(): boolean {
    return relationshipsStore.friendPeerIds.includes(this.user.id)
  }
}
</script>
