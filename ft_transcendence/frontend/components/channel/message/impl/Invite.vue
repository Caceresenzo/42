<template>
  <v-list-item style="align-items: unset">
    <v-list-item-avatar style="align-self: unset">
      <user-avatar :size="40" :user="message.user" without-state />
    </v-list-item-avatar>

    <v-list-item-content class="pt-2 break">
      <v-list-item-title>{{ message.user.username }}</v-list-item-title>
      <p class="text--secondary">{{ status }}</p>
    </v-list-item-content>

    <v-list-item-action>
      <v-btn color="primary" :to="to">{{ buttonText }}</v-btn>
    </v-list-item-action>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Socket } from 'socket.io-client'
import { ChannelMessage } from '~/models'

enum PendinGameState {
  PENDING = 'pending',
  PLAYED = 'played',
}

@Component
export default class XInvite extends Vue {
  @Prop({ type: Object })
  message!: ChannelMessage

  get content() {
    return JSON.parse(this.message.content)
  }

  get state(): PendinGameState {
    return this.content.state
  }

  get buttonText() {
    switch (this.state) {
      case PendinGameState.PENDING: {
        return 'join'
      }

      case PendinGameState.PLAYED: {
        return 'see'
      }
    }
  }

  get status() {
    switch (this.state) {
      case PendinGameState.PENDING: {
        return 'Pending Game'
      }

      case PendinGameState.PLAYED: {
        return 'Played'
      }
    }
  }

  get to() {
    switch (this.state) {
      case PendinGameState.PENDING: {
        return `/pending-games/${this.content.id}`
      }

      case PendinGameState.PLAYED: {
        // TODO
        return `/matches/${this.content.matchId}`
      }
    }
  }
}
</script>

<style scoped>
.break {
  word-break: break-all;
}
</style>
