<template>
  <page-loading v-if="$fetchState.pending" />
  <page-error
    v-else-if="$fetchState.error"
    :error="$fetchState.error"
    @click="$fetch()"
  />
  <v-main v-else class="fill-height" style="overflow-y: auto">
    <v-row class="ma-4">
      <v-col v-if="user.banned" cols="12">
        <v-alert type="error"> This user has been banned </v-alert>
      </v-col>

      <v-col cols="12" md="3">
        <user-profile-card-info :user="user" :game="game" @refresh="$fetch" />
        <user-profile-card-statistics
          :user="user"
          :statistics="statistics"
          :loading="$fetchState.pending"
          class="mt-4"
          @refresh="$fetch"
        />
      </v-col>

      <v-col cols="12" md="6">
        <user-profile-card-matches
          :user="user"
          :matches="matches"
          :loading="$fetchState.pending"
          @refresh="$fetch"
        />
      </v-col>

      <v-col cols="12" md="3">
        <user-profile-card-last-achievements
          :user="user"
          :progresses="progresses"
          :loading="$fetchState.pending"
          @refresh="$fetch"
        />
        <user-profile-card-friends
          :user="user"
          :friends="friends"
          :loading="$fetchState.pending"
          class="mt-4"
          @refresh="$fetch"
        />
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Component, Prop, Vue, Watch } from 'nuxt-property-decorator'
import {
  AchievementProgress,
  Match,
  Relationship,
  User,
  UserStatistics,
} from '~/models'
import { Game } from '~/models/Game'
import { relationshipsStore, socketStore } from '~/store'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Number })
  userId!: number

  user: User | null = null
  matches: Array<Match> = []
  progresses: Array<AchievementProgress> = []
  statistics: UserStatistics | null = null
  friends: Array<Relationship> = []
  game: Game | null = null

  async fetch() {
    this.user = await this.$axios.$get(`/users/${this.userId}`)
    this.matches = await this.$axios.$get(`/users/${this.userId}/matches`)
    this.progresses = await this.$axios.$get(
      `/users/${this.userId}/achievements`
    )
    this.statistics = await this.$axios.$get(`/users/${this.userId}/statistics`)
    this.friends = await this.$axios.$get(`/users/${this.userId}/friends`)

    this.matches.reverse()
    this.friends.reverse()

    this.$axios
      .$get(`/users/@me/relationships/${this.userId}`)
      .then(relationshipsStore.updateItem)
  }

  get playing() {
    return socketStore.playingUserIds.includes(this.userId)
  }

  @Watch('playing', { immediate: true })
  onPlayingUpdate(val: boolean) {
    if (val) {
      this.$axios.$get(`/users/${this.userId}/game`).then((game) => {
        if (this.playing) {
          this.game = game
        }
      })
    } else {
      this.game = null
    }
  }
}
</script>
