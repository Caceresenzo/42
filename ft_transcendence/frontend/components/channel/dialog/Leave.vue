<template>
  <v-btn block color="primary" @click="promptLeave">
    {{ $t('channel.leave.button') }}
    <v-icon right>mdi-logout-variant</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, User } from '~/models'
import { authStore } from '~/store'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  promptLeave() {
    this.$dialog.confirm({
      title: this.$t('channel.leave.title', {
        name: this.channel.name,
      }) as string,
      actions: [
        {
          key: 'yes',
          text: 'Yes',
          color: 'error',
          handler: async () => {
            try {
              const user: User = authStore.user!
              await API.ChannelUsers.destroy(this.channel, user)

              this.$emit('leaved')

              this.$dialog.notify.success('Channel leaved')
            } catch (error) {
              this.$dialog.notify.error(
                error?.response?.data?.errors?.message ||
                  'could not leave the channel'
              )
            }
          },
        },
        {
          key: 'cancel',
          text: 'Cancel',
        },
      ],
    })
  }
}
</script>
