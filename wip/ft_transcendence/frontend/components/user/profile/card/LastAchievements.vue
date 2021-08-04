<template>
  <v-card outlined :loading="loading">
    <v-card-title>
      Achievements
      <v-spacer />
      <v-btn icon :loading="loading" @click="refresh">
        <v-icon>mdi-refresh</v-icon>
      </v-btn>
    </v-card-title>
    <v-list>
      <achievement-empty v-if="!last3.length" />
      <v-list-item v-for="progress in last3" :key="progress.achievement.id">
        <v-list-item-content>
          <achievement-card outlined :progress="progress" />
        </v-list-item-content>
      </v-list-item>
    </v-list>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { AchievementProgress, User } from '~/models'

@Component
export default class Dot extends Vue {
  @Prop()
  user!: User

  @Prop({ type: Array })
  progresses!: Array<AchievementProgress>

  @Prop({ type: Boolean })
  loading!: boolean

  refresh() {
    this.$emit('refresh')
  }

  get last3() {
    return this.progresses
      .filter((x) => x.unlocked)
      .slice(-3)
      .reverse()
  }
}
</script>
