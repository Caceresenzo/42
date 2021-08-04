<template>
  <channel-view-base
    :loading="$fetchState.pending"
    :error="$fetchState.error"
    :loading-message="loadingMessage"
    :title="title"
    :channel="channel"
    :messages="messages"
    @message="onNewMessage"
    @message-update="updateMessage"
  >
    <template v-if="peer" #title>
      <channel-user-menu
        :channel="channel"
        :user="peer"
        bottom
        without-message-button
      >
        <template #activator="{ on, attrs }">
          <v-list-item
            rounded
            shaped
            style="display: inline-block"
            v-bind="attrs"
            v-on="on"
          >
            <v-list-item-avatar>
              <user-avatar :user="peer" :size="40" />
            </v-list-item-avatar>

            <v-list-item-title style="display: inline">
              {{ title }}
            </v-list-item-title>
          </v-list-item>
        </template>
      </channel-user-menu>
    </template>
    <template #toolbar-right>
      <direct-message-button-challenge :peer="directMessage.peer" />
    </template>
  </channel-view-base>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, ChannelMessage, DirectMessage } from '~/models'
import { directMessageStore } from '~/store'

@Component
export default class Viewer extends Vue {
  @Prop({ type: Number })
  peerId!: number

  directMessage: DirectMessage | null = null
  messages: Array<ChannelMessage> = []

  loadingMessage = ''

  async fetch() {
    this.loadingMessage = 'fetching direct messages'

    const directMessage = await API.DirectMessages.show(this.peerId)
    const channel = directMessage.channel

    this.loadingMessage = 'fetching messages'
    const messages = await API.ChannelMessages.index(channel)

    this.loadingMessage = 'connecting to channel'
    await API.Socket.channelConnect(channel)

    this.directMessage = directMessage
    this.messages = messages

    directMessageStore.fetchAll().catch(() => {})
  }

  get channel(): Channel | null {
    return this.directMessage?.channel || null
  }

  get peer() {
    return this.directMessage?.peer
  }

  get title() {
    return this.peer?.username
  }

  onNewMessage(message: ChannelMessage) {
    this.messages.push(message)
  }

  updateMessage(message: ChannelMessage) {
    const { id } = message
    const index = this.messages.findIndex((x) => x.id === id)

    if (index !== -1) {
      this.messages[index].content = message.content
    }
  }
}
</script>
