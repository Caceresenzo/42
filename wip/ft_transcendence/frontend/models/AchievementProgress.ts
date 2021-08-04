import { Achievement } from './Achievement'

export interface AchievementProgress {
  value: number
  unlocked: boolean
  unlockedAt: string | null
  achievement: Achievement
}
