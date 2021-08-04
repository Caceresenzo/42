<template>
  <page-loading v-if="$fetchState.pending" />
  <page-error
    v-else-if="$fetchState.error"
    :error="$fetchState.error"
    @click="$fetch()"
  />
  <v-main v-else class="fill-height" style="overflow: auto">
    <v-row class="ma-2">
      <v-col
        v-for="progress in progresses"
        :key="progress.achievement.id"
        cols="12"
        sm="6"
        md="4"
        lg="3"
      >
        <achievement-card :progress="progress" />
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

import { Achievement, AchievementProgress } from '~/models'
import { meModule } from '~/store/me/const'
import { achievementsStore } from '~/store'

function byId(a: AchievementProgress, b: AchievementProgress) {
  return a.achievement.id - b.achievement.id
}

@Component
export default class Page extends Vue {
  @meModule.State('achievementProgresses')
  achievementProgresses!: AchievementProgress[]

  head() {
    return {
      title: 'Achievements',
    }
  }

  async fetch() {
    if (!this.achievements.length) {
      await achievementsStore.fetchAll()
    }

    await this.$store.dispatch('me/fetch')
  }

  get achievements(): Array<Achievement> {
    return achievementsStore.list
  }

  get progresses(): AchievementProgress[] {
    const ignore = this.achievementProgresses.map((x) => x.achievement.id)

    return [
      ...this.achievementProgresses.slice().sort(byId),
      ...this.achievements
        .filter((x) => !ignore.includes(x.id))
        .map(
          (x): AchievementProgress => ({
            achievement: x,
            value: 0,
            unlocked: false,
            unlockedAt: null,
          })
        )
        .sort(byId),
    ]
  }
}
</script>
