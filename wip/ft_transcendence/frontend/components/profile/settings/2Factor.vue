<template>
  <v-list-item>
    <v-list-item-content>
      <v-switch
        v-model="inputs.enabled"
        :loading="loading"
        :disabled="loading"
        prepend-icon="mdi-two-factor-authentication"
        label="2-Factor Authentication"
        @change="onEnabledChange"
      />
    </v-list-item-content>
    <v-list-item-icon v-if="otp.enabled">
      <v-dialog v-model="dialog" width="500">
        <template #activator="{ on, attrs }">
          <v-btn ref="seeQrcodeButton" color="primary" v-bind="attrs" v-on="on">
            <v-icon left>mdi-qrcode</v-icon>
            see qr-code
          </v-btn>
        </template>

        <v-card>
          <v-card-text class="text-center" style="padding: 24px !important">
            <qrcode :value="otp.uri" :options="{ width: 400 }" />
          </v-card-text>

          <v-divider />

          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn color="primary" text @click="dialog = false"> Close </v-btn>
          </v-card-actions>
        </v-card>
      </v-dialog>
    </v-list-item-icon>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { authStore } from '~/store'

interface OTPState {
  enabled: boolean
  uri: string | null
}

@Component
export default class Dot extends Vue {
  dialog = false

  loading = false
  error: any = null

  inputs = {
    enabled: false,
  }

  otp: OTPState = {
    enabled: false,
    uri: null,
  }

  async fetch() {
    this.loading = true
    this.error = null

    try {
      this.otp = await this.$axios.$get(`/users/@me/profile/settings/otp`)

      this.inputs.enabled = this.otp.enabled
    } catch (error) {
      this.error = error
    }

    this.loading = false
  }

  async onEnabledChange(enabled: boolean) {
    const cancel = () => (this.inputs.enabled = !enabled)

    if (this.loading) {
      cancel()
      return
    }

    this.loading = true
    this.error = null

    try {
      this.otp = await this.$axios.$request({
        method: enabled ? 'POST' : 'DELETE',
        url: `/users/@me/profile/settings/otp`,
      })

      if (enabled) {
        this.$nextTick(() => {
          ;(this.$refs.seeQrcodeButton as any)?.$el?.click()
        })

        this.$dialog.notify.info('2 Factor Authentication enabled!')
      } else {
        this.$dialog.notify.warning('2 Factor Authentication disabled!')
      }
    } catch (error) {
      cancel()

      if (enabled) {
        this.$dialog.notify.error('Could not enabled!')
      } else {
        this.$dialog.notify.error('Could not disabled!')
      }

      this.error = error
    }

    this.loading = false
  }

  get user(): User | null {
    return authStore.user
  }
}
</script>
