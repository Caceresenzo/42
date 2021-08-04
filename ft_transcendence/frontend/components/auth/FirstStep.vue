<template>
  <page-centered>
    <div style="max-width: 300px">
      <user-avatar :user="user" :size="128" without-state />
      <v-card-title>
        <v-spacer />
        {{ username }}
        <v-spacer />
      </v-card-title>
      <v-text-field
        v-model="username"
        :loading="loading"
        :disabled="loading"
        :error-messages="error"
        label="Username"
        prepend-inner-icon="mdi-rename-box"
        solo
        @keypress.enter="submit()"
      />
      <v-card-actions>
        <v-spacer />
        <v-btn :loading="loading" color="primary" @click="submit()">
          finalize registration
        </v-btn>
        <v-spacer />
      </v-card-actions>
    </div>
  </page-centered>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { authStore } from '~/store'

@Component({
  layout: 'empty',
})
export default class Callback extends Vue {
  @Prop()
  user!: User

  username: string = ''

  error: any = null
  loading = false

  async submit() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    try {
      const user: User = await this.$axios.$post(
        '/auth/finalize-registration',
        {
          username: this.username,
        }
      )

      authStore.setUser(user)

      this.$router.push({ path: '/' })

      setTimeout(
        () => this.$dialog.notify.success(`Welcome ${user.username}!`),
        1000
      )
    } catch (error) {
      switch (error.response?.status) {
        /* bad format */
        case 400: {
          this.error = 'bad format'
          break
        }

        /* already finalized */
        case 403: {
          this.$router.push({ path: '/' })
          setTimeout(
            () => this.$dialog.notify.error(`Cannot finalize multiple time`),
            1000
          )
          break
        }

        /* already taken */
        case 409: {
          this.error = 'already taken'
          break
        }

        default: {
          this.error = error.toString()
          break
        }
      }
    }

    this.loading = false
  }

  mounted() {
    this.username = this.user.username
  }
}
</script>
