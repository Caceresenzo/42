<template>
  <v-card elevation="0" outlined :to="to">
    <v-card-title v-if="user">
      <v-spacer />
      <user-avatar :user="user" />
      <v-spacer />
    </v-card-title>
    <v-card-title>
      <v-spacer />
      <v-icon left :color="color">
        {{ icon }}
      </v-icon>
      {{ username }}
      <v-spacer />
    </v-card-title>
    <v-card-title>
      <v-spacer />
      {{ score }}
      <v-spacer />
    </v-card-title>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { Player } from '~/models/Game'

@Component
export default class PlayerCard extends Vue {
  @Prop()
  player!: Player

  @Prop()
  winner!: User

  get icon(): string {
    if (this.isWinner) {
      return 'mdi-crown'
    }

    return 'mdi-trophy-broken'
  }

  get color(): string {
    if (this.isWinner) {
      return 'yellow'
    }

    return 'red'
  }

  get user(): User | null {
    return this.player?.user
  }

  get to(): string | null {
    if (this.user) {
      return `/users/${this.user.id}`
    }

    return null
  }

  get isWinner(): boolean {
    return this.user?.id === this.winner?.id
  }

  get username() {
    return this.user?.username || '???'
  }

  get score(): string {
    const score = this.player?.score

    if (score === undefined) {
      return '?'
    }

    return `${score}`
  }
}
</script>
