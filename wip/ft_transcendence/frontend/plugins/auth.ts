import { Plugin } from '@nuxt/types'

const plugin: Plugin = async ({ store, redirect }) => {
  await store.dispatch('auth/restoreTokens')

  if (store.state.auth.accessToken) {
    try {
      await store.dispatch('auth/fetch')

      return /* good */
    } catch (error) {
      console.error(error)
      await store.dispatch('auth/clearTokens')
    }
  }

  redirect('/auth')
}

export default plugin
