<template>
  <page-loading title="redirecting..." />
</template>

<script lang="ts">
import { Context } from '@nuxt/types'
import { Component, Vue } from 'nuxt-property-decorator'
import { authStore } from '~/store'

@Component({
  layout: 'empty',
})
export default class Redirect extends Vue {
  validate({ params, store }: Context) {
    const { provider } = params

    return provider in store.state.auth.providers
  }

  head() {
    return {
      title: `Redirecting to ${this.provider} - Authentication`,
    }
  }

  async redirect(): Promise<boolean> {
    try {
      await this.$axios.$get('/ping')

      document.location = this.oauthUrl as any

      return true
    } catch (error) {
      console.log(error)
    }

    await new Promise((resolve) => setTimeout(resolve, 500))

    return false
  }

  async mounted() {
    if (window.opener) {
      while (!(await this.redirect())) {
        continue
      }
    } else {
      this.$router.push('/auth')
    }
  }

  get oauthUrl() {
    return `/api/auth/oauth/${this.provider}`
  }

  get provider() {
    return this.$route.params.provider
  }
}
</script>
