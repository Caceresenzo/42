<template>
  <v-text-field
    ref="textField"
    v-model="content"
    :disabled="loading"
    background-color="grey lighten-1"
    dense
    solo
    class="mt-2"
    @keydown.enter="submit"
  >
    <template #append-outer>
      <v-btn :loading="loading" icon class="ml-2" @click="submit">
        <v-icon>mdi-send</v-icon>
      </v-btn>
    </template>
  </v-text-field>
</template>

<script lang="ts">
import { Component, Watch, Vue, Prop } from 'nuxt-property-decorator'
import API from '~/api/API'

import { Channel, ChannelMessageContentType } from '~/models'

@Component
export default class Input extends Vue {
  @Prop()
  channel!: Channel

  content = ''
  loading = false

  @Watch('loading')
  onLoadingChange(val: boolean) {
    if (!val) {
      this.$nextTick(() => (this.$refs.textField as any).focus())
    }
  }

  async submit() {
    if (this.loading) {
      return
    }

    this.loading = true

    try {
      await API.ChannelMessages.create(this.channel, {
        type: ChannelMessageContentType.TEXT,
        content: this.content,
      })

      this.content = ''
    } catch (error) {
      const reason =
        error.response?.data?.errors?.message || 'could not send message'

      this.$dialog.notify.error(reason)
    }

    this.loading = false
  }
}
</script>
