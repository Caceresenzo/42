<template>
  <page-centered>
    <div style="max-width: 300px">
      <user-avatar :user="user" :size="128" without-state />
      <v-card-title>
        <v-spacer />
        {{ user.username }}
        <v-spacer />
      </v-card-title>
      <v-alert color="error" outlined>
        <v-text-field
          v-model="otp"
          label="OTP"
          hide-details
          @keypress.enter="onOtpCode()"
        />
      </v-alert>
    </div>
  </page-centered>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'

@Component({
  layout: 'empty',
})
export default class Callback extends Vue {
  @Prop()
  user!: User

  otp: string = ''

  onOtpCode() {
    this.$emit('otp-code', this.otp)
  }
}
</script>
