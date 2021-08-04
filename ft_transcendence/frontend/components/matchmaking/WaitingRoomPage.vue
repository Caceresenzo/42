<template>
  <page-loading v-if="loading" title="Joining waiting room..." />
  <page-error v-else-if="error" :error="error" @click="tryJoin" />
  <page-loading v-else-if="joined" title="Waiting for opponent..." />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Socket } from 'vue-socket.io-extended'
import { PendingGame } from '~/models'
import { Game } from '~/models/Game'
import { authStore } from '~/store'

@Component
export default class Page extends Vue {
  @Prop()
  pendingGame!: PendingGame

  loading = false
  joined = false
  error: any = null

  get id() {
    return this.pendingGame?.id || 0
  }

  mounted() {
    this.tryJoin()
  }

  tryJoin() {
    this.loading = true
    this.error = null

    this.$socket.client.emit(
      'waiting_room_join',
      {
        id: this.id,
      },
      async (error: any) => {
        if (error) {
          const message = error.message

          if (message === 'already in game') {
            await this.tryRejoin(error)
          } else {
            this.error = error
          }
        } else {
          this.joined = true
        }

        this.loading = false
      }
    )
  }

  async tryRejoin(error: any) {
    try {
      const game = await this.$axios.$get(`/users/${authStore.user?.id}/game`)

      this.$dialog.notify.info('You are currently in a game')
      this.onGameStarting(game)
    } catch (error2) {
      console.log('Error when trying to fetch game', error2)

      this.error = error
    }
  }

  @Socket('game_connect')
  onGameStarting(data: Game) {
    const { id } = data

    this.joined = true
    this.$router.push({ path: `/games/${id}` })
  }

  beforeDestroy() {
    this.$socket.client.emit('waiting_room_leave')
  }
}
</script>
