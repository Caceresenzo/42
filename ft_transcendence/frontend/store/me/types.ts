import { ActionContext, ActionTree, MutationTree, Store } from 'vuex'
import { RootState } from '../types'
import { AchievementProgress, Relationship } from '~/models'

export interface MeStateState {
  achievementProgresses: AchievementProgress[]
  relationships: Relationship[]
}

export type MeStateActionContext = ActionContext<MeStateState, RootState>
export type MeStateStore = Store<RootState>

export interface MeStateActions extends ActionTree<MeStateState, RootState> {
  fetch(this: MeStateStore, context: MeStateActionContext): void

  fetchRelationships(this: MeStateStore, context: MeStateActionContext): void
}

export interface MeStateMutations extends MutationTree<MeStateState> {
  setAchievementProgresses(
    state: MeStateState,
    progresses: AchievementProgress[]
  ): void

  setRelationships(state: MeStateState, relationships: Relationship[]): void
}
