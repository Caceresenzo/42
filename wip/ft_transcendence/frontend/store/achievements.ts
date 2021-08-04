import { Action, Module, Mutation, VuexModule } from 'vuex-module-decorators'
import AchievementsAPI from '~/api/AchievementsAPI'
import { Achievement } from '~/models'

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'achievements',
})
class AchievementsModule extends VuexModule {
  list: Array<Achievement> = []

  @Mutation
  set(list: Array<Achievement>) {
    this.list = list
  }

  @Action({ commit: 'set', rawError: true })
  async fetchAll() {
    const achievements = await AchievementsAPI.index()

    return achievements
  }
}

export default AchievementsModule
