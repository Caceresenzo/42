<template>
  <v-btn block color="primary" :loading="loading" @click="submit()">
    {{ $t('channel.join.button') }}
  </v-btn>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'

import { Channel } from '~/models'
import { authStore } from '~/store'

@Component
export default class Input extends Vue {
  @Prop()
  channel!: Channel

  loading = false
  error: any = null

  async submit() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    const userId = authStore.user!.id

    try {
      await API.ChannelUsers.create(this.channel, userId)

      this.$emit('joined')
    } catch (error) {
      this.error = error
      alert(error)
    }

    this.loading = false
  }
}
</script>
