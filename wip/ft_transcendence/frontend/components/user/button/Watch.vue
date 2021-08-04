<template>
  <v-btn depressed block color="warning" :to="to">
    watch
    <v-icon right>mdi-eye</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Game } from '~/models/Game'

@Component
export default class Watch extends Vue {
  @Prop()
  game!: Game

  get to() {
    return `/games/${this.game.id}`
  }
}
</script>
