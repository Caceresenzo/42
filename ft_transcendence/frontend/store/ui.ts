import { Module, VuexModule, Mutation } from 'vuex-module-decorators'

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'ui',
})
class UIModule extends VuexModule {
  drawer = true

  @Mutation
  setDrawer(value: boolean) {
    this.drawer = value
  }

  get smallScreen() {
    return ['xs', 'sm', 'md'].includes(
      window.$nuxt.$root.$vuetify.breakpoint.name
    )
  }
}

export default UIModule
