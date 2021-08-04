<template>
  <v-menu
    v-model="menu"
    :close-on-content-click="false"
    :offset-y="bottom"
    :offset-x="!bottom"
    :left="!bottom"
  >
    <template #activator="{ on, attrs }">
      <slot name="activator" :on="on" :attrs="attrs" />
    </template>

    <v-card :loading="loading">
      <v-list>
        <v-list-item>
          <v-list-item-avatar>
            <user-avatar :size="40" :user="user" />
          </v-list-item-avatar>

          <v-list-item-content>
            <v-list-item-title>{{ user.username }}</v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list>

      <v-divider />

      <template v-if="statistics">
        <user-statistics :statistics="statistics" />
        <v-divider />
      </template>

      <template v-else-if="error">
        <v-card-text> could not fetch user statistics </v-card-text>
        <v-divider />
      </template>

      <v-card-actions>
        <v-spacer />

        <v-btn text :to="toProfile" color="primary"> profile </v-btn>
        <v-btn v-if="!withoutMessageButton" text :to="toMessage">
          message
        </v-btn>
        <v-btn v-if="game" text :to="toGame"> Watch game </v-btn>
      </v-card-actions>
    </v-card>
  </v-menu>
</template>

<script lang="ts">
import { Component, Prop, Vue, Watch } from 'nuxt-property-decorator'

import { Channel, ChannelUser, UserStatistics } from '~/models'
import { socketStore } from '~/store'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Object })
  user!: ChannelUser

  @Prop({ type: Boolean })
  bottom!: boolean

  @Prop({ type: Boolean })
  withoutMessageButton!: boolean

  menu = false
  loading = false
  error: any = null

  statistics: UserStatistics | null = null
  game: any | null = null

  async fetchStatistics() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    try {
      this.statistics = await this.$axios.$get(
        `/users/${this.user.id}/statistics`
      )
    } catch (error) {
      this.error = error
    }

    this.loading = false
  }

  async fetchGame() {
    try {
      this.game = await this.$axios.$get(`/users/${this.user.id}/game`)
    } catch (error) {
      this.$dialog.notify.error(`Could not fetch user game: ${error}`)
    }
  }

  get playing(): boolean {
    return socketStore.playingUserIds.includes(this.user.id)
  }

  get toProfile() {
    return `/users/${this.user.id}`
  }

  get toMessage() {
    return `/direct-messages/${this.user.id}`
  }

  get toGame() {
    if (!this.game) {
      return null
    }

    return `/games/${this.game.id}`
  }

  @Watch('menu')
  onMenuOpenStateUpdate(val: boolean) {
    if (val) {
      this.fetchStatistics()

      if (this.playing) {
        this.fetchGame()
      }
    }
  }

  @Watch('playing')
  onPlayingUpdate(val: boolean) {
    this.game = null

    if (val && this.menu) {
      this.fetchGame()
    }
  }
}
</script>
