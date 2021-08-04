<template>
  <v-main class="fill-height" style="overflow: auto">
    <v-row class="ma-2">
      <v-col cols="12">
        <v-card>
          <v-card-title>Match Results</v-card-title>
          <v-card-text>
            <v-row>
              <v-col
                v-for="(player, index) in [left, right]"
                :key="index"
                cols="12"
                sm="6"
              >
                <match-player-card :player="player" :winner="winner" />
              </v-col>
            </v-row>
          </v-card-text>
        </v-card>
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Context } from '@nuxt/types'
import { Component, Vue } from 'nuxt-property-decorator'
import { Match, User } from '~/models'
import { Player, Side } from '~/models/Game'

@Component
export default class Page extends Vue {
  match!: Match

  async asyncData({ $axios, params }: Context) {
    const { id } = params

    const match = await $axios.$get(`/matches/${id}`)

    return {
      match,
    }
  }

  get left(): Player {
    return this.match.player[Side.LEFT]
  }

  get right(): Player {
    return this.match.player[Side.RIGHT]
  }

  get winner(): User {
    return this.match.winner
  }
}
</script>
