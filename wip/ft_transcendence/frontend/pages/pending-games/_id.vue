<template>
  <matchmaking-waiting-room-page :pending-game="pendingGame" />
</template>

<script lang="ts">
import { Context } from '@nuxt/types'
import { Component, Vue } from 'nuxt-property-decorator'
import { PendingGame } from '~/models'

@Component
export default class Page extends Vue {
  pendingGame!: PendingGame

  async asyncData({ params, $axios }: Context) {
    const { id } = params

    const pendingGame: PendingGame = await $axios.$get(`/pending-games/${id}`)

    return {
      pendingGame,
    }
  }
}
</script>
