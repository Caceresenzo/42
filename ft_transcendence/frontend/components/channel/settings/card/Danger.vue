<template>
  <v-card>
    <v-alert outlined color="red" class="pa-0">
      <v-card-title> {{ $t('channel.settings.danger.title') }} </v-card-title>
      <v-card-text>
        <v-btn color="error" @click="confirmClearMessages()">
          {{ $t('channel.settings.danger.actions.clear-messages._') }}
        </v-btn>
        <v-btn color="error" class="ml-2" @click="confirmDeleteChannel()">
          {{ $t('channel.settings.danger.actions.delete-channel._') }}
        </v-btn>
      </v-card-text>
    </v-alert>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel } from '~/models'

@Component
export default class Edit extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  confirmClearMessages() {
    this.$confirm(
      this.$t(
        'channel.settings.danger.actions.clear-messages.confirm'
      ) as string
    ).then(async (response) => {
      if (response) {
        try {
          await this.$axios.delete(`/channels/${this.channel.id}/messages`)
          this.$router.push(`/channels/${this.channel.id}`)

          this.$dialog.notify.success('Successfully cleared messages')
        } catch (error) {
          this.$dialog.notify.error(
            `Could not clear messages: ${
              error?.response?.data?.errors?.message || error
            }`
          )
        }
      }
    })
  }

  confirmDeleteChannel() {
    this.$confirm(
      this.$t(
        'channel.settings.danger.actions.delete-channel.confirm'
      ) as string
    ).then(async (response) => {
      if (response) {
        try {
          await this.$axios.delete(`/channels/${this.channel.id}`)
          this.$store.dispatch('channels/fetchAll')
          this.$router.push('/channels')
        } catch (error) {
          this.$dialog.notify.error(
            `Could not delete channel: ${
              error?.response?.data?.errors?.message || error
            }`
          )
        }
      }
    })
  }
}
</script>
