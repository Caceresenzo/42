<template>
  <v-card :outlined="outlined">
    <v-card-title>
      {{ name }}
      <template v-if="icon">
        <v-spacer />
        <v-icon>{{ icon }}</v-icon>
      </template>
    </v-card-title>
    <v-card-subtitle>{{ description }}</v-card-subtitle>
    <v-progress-linear :value="percentage" height="25">
      <small v-if="isUnlocked">{{ unlockedAt }}</small>
      <template v-else>
        <small v-if="isPercent">{{ percentage.toFixed(2) }}</small>
        <small v-else>
          {{ progress.value }} / {{ progress.achievement.max }}
        </small>
      </template>
    </v-progress-linear>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

import { AchievementProgress } from '~/models'

import { Icons } from '~/game/Achievements'

@Component
export default class Page extends Vue {
  @Prop()
  progress!: AchievementProgress

  @Prop({ type: Boolean, default: false })
  outlined!: boolean

  get name(): string {
    return this.progress.achievement.name
  }

  get description(): string {
    return this.progress.achievement.description
  }

  get isUnlocked(): boolean {
    return this.progress.unlocked
  }

  get unlockedAt(): string {
    return new Date(this.progress.unlockedAt as string).toLocaleString()
  }

  get isPercent(): boolean {
    return this.progress.achievement.percent
  }

  get percentage(): number {
    return (this.progress.value / this.progress.achievement.max) * 100
  }

  get icon(): string | null {
    const id = this.progress.achievement.id

    return (Icons as any)[`${id}`] || null
  }
}
</script>
