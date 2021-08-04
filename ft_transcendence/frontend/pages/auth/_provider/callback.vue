<template>
  <auth-2-factor
    v-if="phase === '2fa'"
    :user="phaseToken.user"
    @otp-code="unlock"
  />
  <page-loading v-else title="authenticating..." />
</template>

<script lang="ts">
import { Context } from '@nuxt/types'
import { Component, Vue } from 'nuxt-property-decorator'
import { Phase, PhaseToken } from '~/models'
import { authStore } from '~/store'

@Component({
  layout: 'empty',
})
export default class Callback extends Vue {
  profile: any = null
  phaseToken: PhaseToken | null = null

  validate({ params, store }: Context) {
    const { provider } = params

    return provider in store.state.auth.providers
  }

  head() {
    return {
      title: `${this.provider} - Authentication`,
    }
  }

  mounted() {
    if (window.opener) {
      window.opener.postMessage('fetching', '*')

      this.$axios
        .get(this.callbackUrl, {
          params: {
            code: this.code,
          },
        })
        .then(async (response) => {
          const { accessToken, refreshToken } = response.data

          authStore.updateTokens({
            accessToken,
            refreshToken,
          })

          await authStore.fetch()

          this.post('success')
          this.closeWindow()
        })
        .catch((error) => {
          console.log(error)

          if (error.response?.status === 402) {
            this.phaseToken = error.response.data
          } else if (error.response?.status === 403) {
            this.post(`banned`)
            this.closeWindow()
          } else {
            this.post(`error`)
            this.closeWindow()
          }
        })
    } else {
      this.$router.push('/auth')
    }
  }

  unlock(code: string) {
    if (window.opener) {
      window.opener.postMessage('unlocking', '*')

      let otp: any
      if (this.phase === Phase.TWO_FACTOR) {
        otp = code
      }

      this.$axios
        .post('/auth/unlock', {
          token: this.phaseToken?.token,
          phase: this.phase,
          otp,
        })
        .then(async (response) => {
          const { accessToken, refreshToken } = response.data

          authStore.updateTokens({
            accessToken,
            refreshToken,
          })

          await authStore.fetch()

          this.post('unlock-success')
          this.closeWindow()
        })
        .catch((error) => {
          console.log(error)

          this.post(`unlock-error`)
          this.closeWindow()
        })
    } else {
      this.$router.push('/auth')
    }
  }

  get provider() {
    return this.$route.params.provider
  }

  get code() {
    return this.$route.query.code
  }

  get callbackUrl() {
    return `/auth/oauth/${this.provider}/callback`
  }

  get phase() {
    return this.phaseToken?.phase
  }

  post(event: string) {
    window.opener?.postMessage(event, '*')
  }

  closeWindow() {
    setTimeout(() => window.close(), 10)
  }
}
</script>
