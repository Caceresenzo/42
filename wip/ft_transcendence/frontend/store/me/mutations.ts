import { MeStateMutations } from './types'

export const mutations: MeStateMutations = {
  setAchievementProgresses(state, progresses) {
    state.achievementProgresses = progresses
  },

  setRelationships(state, relationships) {
    state.relationships = relationships
  },
}

export default mutations
