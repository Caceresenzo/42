import { MeStateActions } from './types'
import { AchievementProgress, Relationship } from '~/models'

export const actions: MeStateActions = {
  async fetch({ commit }) {
    const progresses: AchievementProgress[] = await this.$axios.$get(
      '/users/@me/achievements'
    )

    commit('setAchievementProgresses', progresses)
  },

  async fetchRelationships({ commit }) {
    const relationships: Relationship[] = await this.$axios.$get(
      '/users/@me/relationships'
    )

    commit('setRelationships', relationships)
  },
}

export default actions
