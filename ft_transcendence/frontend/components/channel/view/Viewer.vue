<template>
  <channel-view-base
    :loading="$fetchState.pending"
    :error="$fetchState.error"
    :loading-message="loadingMessage"
    :title="title"
    :channel="channel"
    :messages="messages"
    @updated="onUpdate"
    @deleted="onDeleted"
    @message="onNewMessage"
    @message-deleted="onMessageDelete"
    @message-deleted-all="onClear"
    @joined="onUserJoin"
    @leaved="onUserLeave"
    @update="onUserUpdate"
    @transfer="onOwnerTransfer"
  >
    <template slot="toolbar-right">
      <v-btn v-model="rightDrawer" icon @click="rightDrawer = !rightDrawer">
        <v-icon>mdi-account-group</v-icon>
      </v-btn>
    </template>

    <template slot="input">
      <channel-message-input
        v-if="hasJoined || isSiteAdmin"
        :channel="channel"
      />
      <channel-join v-else :channel="channel" @joined="onJoined" />
    </template>

    <channel-drawer-right
      v-model="rightDrawer"
      :channel="channel"
      :users="users"
      :has-joined="hasJoined"
      :is-site-admin="isSiteAdmin"
      :is-owner="isOwner"
      :is-admin="isAdmin"
      :loading="$fetchState.pending"
      @refresh="$fetch()"
      @joined="onJoined"
      @leaved="onLeaved"
    />
  </channel-view-base>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, ChannelMessage, ChannelUser, User } from '~/models'
import { authStore, channelsStore } from '~/store'

@Component
export default class Viewer extends Vue {
  @Prop({ type: Number })
  id!: number

  channel: Channel | null = null
  users: Array<ChannelUser> = []
  messages: Array<ChannelMessage> = []

  rightDrawer = true

  loadingMessage = ''

  async fetch() {
    this.loadingMessage = 'fetching channel'
    const channel = await API.Channels.show(this.id)

    this.loadingMessage = 'fetching users'
    const users = await API.ChannelUsers.index(channel)

    this.loadingMessage = 'fetching messages'
    const messages = await API.ChannelMessages.index(channel)

    this.loadingMessage = 'connecting to channel'
    await API.Socket.channelConnect(channel)

    this.channel = channel
    this.users = users
    this.messages = messages
  }

  onUpdate(channel: Channel) {
    if (this.channel?.id === channel.id) {
      this.channel = channel
    }
  }

  onDeleted(channel: Channel) {
    channelsStore.deleteItem(channel)

    this.$router.push({ path: '/channels' })
    this.$dialog.notify.info('The channel has been deleted')
  }

  onNewMessage(message: ChannelMessage) {
    this.messages.push(message)
  }

  onMessageDelete(message: ChannelMessage) {
    const { id } = message
    const index = this.messages.findIndex((x) => x.id === id)

    if (index !== -1) {
      this.messages.splice(index, 1)
    }
  }

  onClear(_channel: Channel) {
    this.messages.splice(0)
  }

  onUserJoin(channelUser: ChannelUser) {
    this.users.push(channelUser)
  }

  onUserLeave(channelUser: ChannelUser) {
    const index = this.getChannelUserIndex(channelUser)

    if (index !== -1) {
      this.users.splice(index, 1)
    }
  }

  onUserUpdate(channelUser: ChannelUser) {
    const index = this.getChannelUserIndex(channelUser)

    if (index !== -1) {
      const previous = this.users[index]
      this.$set(this.users, index, channelUser)

      if (channelUser.id === authStore.user!.id) {
        if (channelUser.banned) {
          this.$router.push({ path: '/channels' })
          this.$dialog.notify.error('banned')
        }

        if (channelUser.muted !== previous.muted) {
          if (channelUser.muted) {
            this.$dialog.notify.warning('muted')
          } else {
            this.$dialog.notify.success('unmuted')
          }
        }

        if (channelUser.admin !== previous.admin) {
          if (channelUser.admin) {
            this.$dialog.notify.success('promoted')
          } else {
            this.$dialog.notify.warning('demoted')
          }
        }
      }
    }
  }

  onOwnerTransfer(user: User) {
    const previous = this.channel!.owner

    if (previous.id !== user.id) {
      this.channel!.owner = user

      if (user.id === authStore.user!.id) {
        this.$dialog.notify.success('ownership transfered to you')
      } else if (previous.id === authStore.user!.id) {
        this.$dialog.notify.warning('ownership transfered')
      }
    }
  }

  getChannelUserIndex(channelUser: ChannelUser) {
    return this.users.map((x) => x.id).indexOf(channelUser.id)
  }

  get selfChannelUser() {
    const userId = authStore.user!.id

    return this.users.filter((x) => x.id === userId)[0]
  }

  get hasJoined() {
    return !!this.selfChannelUser || false
  }

  get isOwner() {
    const user = authStore.user!

    if (this.id && this.channel) {
      return this.channel.owner.id === user.id
    }

    return false
  }

  get isAdmin() {
    return this.selfChannelUser?.admin || authStore.user!.admin
  }

  get isSiteAdmin() {
    return authStore.user!.admin
  }

  get title() {
    return this.channel?.name
  }

  onJoined() {
    this.$store.dispatch('channels/fetchAll')
    this.$fetch()
  }

  onLeaved() {
    this.$store.dispatch('channels/fetchAll')
  }
}
</script>
