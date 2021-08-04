<template>
  <v-card outlined :loading="loading">
    <v-card-title>
      Matches
      <v-spacer />
      <v-btn icon :loading="loading" @click="refresh">
        <v-icon>mdi-refresh</v-icon>
      </v-btn>
    </v-card-title>

    <v-divider />

    <v-data-table
      :headers="headers"
      :items="matches"
      :items-per-page="10"
      hide-default-header
      @click:row="onRowClick"
    >
      <template #item.against="{ item }">
        <user-avatar class="my-2" :user="getEnemy(item)" />
      </template>
      <template #item.message="{ item }">
        <span v-if="hasWon(item)" class="yellow--text">Won</span>
        <span v-else class="red--text">Lost</span>
        against {{ getEnemy(item).username }}
      </template>
      <template #item.score="{ item }">
        <h2>{{ getPlayerScore(item) }} - {{ getEnemyScore(item) }}</h2>
      </template>
      <template #item.emoticon="{ item }">
        <v-icon v-if="hasWon(item)" large color="yellow">
          mdi-emoticon-cool
        </v-icon>
        <v-icon v-else large color="red">mdi-emoticon-dead</v-icon>
      </template>
    </v-data-table>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Match, User } from '~/models'
import { Player, Side } from '~/models/Game'

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  user!: User

  @Prop({ type: Array })
  matches!: Array<Match>

  @Prop({ type: Boolean })
  loading!: boolean

  headers = [
    { align: 'left', sortable: false, value: 'against' },
    { align: 'left', sortable: false, value: 'message' },
    { align: 'left', sortable: false, value: 'score' },
    { align: 'left', sortable: false, value: 'emoticon' },
  ]

  refresh() {
    this.$emit('refresh')
  }

  to(match: Match) {
    return `/matches/${match.id}`
  }

  hasWon(match: Match): boolean {
    return this.user.id === match.winner.id
  }

  getPlayer(match: Match): User {
    return this.getSidedPlayer(true, match).user
  }

  getEnemy(match: Match): User {
    return this.getSidedPlayer(false, match).user
  }

  getPlayerScore(match: Match): number {
    return this.getSidedPlayer(true, match).score
  }

  getEnemyScore(match: Match): number {
    return this.getSidedPlayer(false, match).score
  }

  getSidedPlayer(me: boolean, match: Match): Player {
    return match.player[this.getSide(me, match)]
  }

  getSide(mine: boolean, match: Match): Side {
    if (this.user.id === match.player[Side.LEFT].user.id) {
      return mine ? Side.LEFT : Side.RIGHT
    } else {
      return mine ? Side.RIGHT : Side.LEFT
    }
  }

  onRowClick(match: Match) {
    this.$router.push({ path: this.to(match) })
  }
}
</script>
