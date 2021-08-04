<template>
  <v-main>
    <v-container fill-height fluid>
      <v-row align="center">
        <v-col align="center">
          <h1>ft-transcendence</h1>
          <div class="text-center mt-16" style="max-width: 400px">
            <auth-state-alert :state="state" />
            <v-progress-linear v-if="loading" indeterminate />
            <v-btn
              v-for="(provider, key) in providers"
              :key="key"
              color="primary"
              block
              x-large
              class="my-2"
              :disabled="loading"
              @click="use(key)"
            >
              {{ provider.name }}
            </v-btn>
          </div>
        </v-col>
      </v-row>
    </v-container>
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { AuthProvider } from '~/models'
import { authStore } from '~/store'

@Component({
  layout: 'empty',
})
export default class Index extends Vue {
  loading = false
  state: string | null = null

  head() {
    return {
      title: 'Authentication',
    }
  }

  use(key: string) {
    if (this.loading) {
      return
    }

    const provider = this.providers[key]

    this.state = null
    this.loading = true

    const onMessage = async (event: MessageEvent) => {
      let done = false

      console.log(event.data)

      switch (event.data) {
        case 'fetching':
        case 'unlocking': {
          break
        }

        case 'success':
        case 'unlock-success': {
          authStore.restoreTokens()
          await authStore.fetch()

          this.$router.push('/')

          done = true
          break
        }

        case 'error':
        case 'unlock-error':
        case 'banned': {
          done = true
          break
        }

        default: {
          return
        }
      }

      this.state = event.data

      if (done) {
        this.loading = false
        window.removeEventListener('message', onMessage)
      }
    }

    window.addEventListener('message', onMessage)

    const width = provider.width
    const height = provider.height
    const left = Math.round(window.screenX + (window.outerWidth - width) / 2)
    const top = Math.round(window.screenY + (window.outerHeight - height) / 2.5)

    const url = `/auth/${key}/redirect`

    const childWindow = window.open(
      url,
      'LogIn',
      'width=' +
        width +
        ',height=' +
        height +
        ',left=' +
        left +
        ',top=' +
        top +
        ',toolbar=0,scrollbars=0,status=0,resizable=0,location=0,menuBar=0'
    )

    if (childWindow) {
      const timerId = setInterval(() => {
        if (childWindow.closed) {
          clearInterval(timerId)
          this.loading = false
        }
      }, 100)
    }
  }

  get providers(): { [key: string]: AuthProvider } {
    return authStore.providers
  }
}
</script>
