<template>
  <channel-view-loading v-if="loading && !channel" :message="loadingMessage" />
  <channel-view-error v-else-if="error" :error="error" @refresh="refresh" />
  <div v-else class="fill-height">
    <v-app-bar app clipped-right>
      <v-toolbar-title>
        <drawer-menu />
        <div style="display: inline-block">
          <slot name="title">
            {{ title }}
          </slot>
        </div>
      </v-toolbar-title>
      <template v-if="$scopedSlots['toolbar-right']">
        <v-spacer />
        <slot name="toolbar-right" />
      </template>
    </v-app-bar>

    <v-card class="mx-auto fill-height">
      <v-list class="fill-height">
        <virtual-list
          ref="virtualMessageList"
          class="fill-height"
          style="overflow-y: auto"
          data-key="id"
          :data-sources="messages"
          :data-component="itemComponent"
        />
      </v-list>
    </v-card>

    <v-footer app height="72" inset>
      <slot name="input">
        <channel-message-input :channel="channel" />
      </slot>
    </v-footer>

    <slot />
  </div>
</template>

<script lang="ts">
import { Component, Prop, Vue, Watch } from 'nuxt-property-decorator'
import { Socket } from 'vue-socket.io-extended'
import ScrollItem from '~/components/channel/message/ScrollItem.vue'
import { Channel, ChannelMessage, ChannelUser, User } from '~/models'

@Component
export default class Viewer extends Vue {
  @Prop({ type: Boolean, default: false })
  loading!: boolean

  @Prop({ type: String })
  loadingMessage!: string

  @Prop()
  error!: any

  @Prop({ type: String })
  title!: string

  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Array })
  messages!: Array<ChannelMessage>

  @Watch('messages')
  onNewMessage() {
    this.scrollToBotton()
  }

  @Watch('loading')
  onFetchFinished(val: boolean) {
    if (!val) {
      setTimeout(() => this.scrollToBotton(), 100)
    }
  }

  @Socket('channel_update')
  onChannelUpdate(channel: Channel) {
    this.$emit('updated', channel)
  }

  @Socket('channel_delete')
  onChannelDelete(channel: Channel) {
    this.$emit('deleted', channel)
  }

  @Socket('channel_message')
  onChannelMessage(message: ChannelMessage) {
    this.$emit('message', message)
  }

  @Socket('channel_message_update')
  onChannelMessageUpdate(message: ChannelMessage) {
    this.$emit('message-update', message)
  }

  @Socket('channel_message_delete')
  onChannelMessageDelete(message: ChannelMessage) {
    this.$emit('message-deleted', message)
  }

  @Socket('channel_message_delete_all')
  onChannelMessageDeleteAll(channel: Channel) {
    this.$emit('message-deleted-all', channel)
  }

  @Socket('channel_user_join')
  onChannelUserJoin(channelUser: ChannelUser) {
    this.$emit('joined', channelUser)
  }

  @Socket('channel_user_leave')
  onChannelUserLeave(channelUser: ChannelUser) {
    this.$emit('leaved', channelUser)
  }

  @Socket('channel_user_update')
  onChannelUserUpdate(channelUser: ChannelUser) {
    this.$emit('update', channelUser)
  }

  @Socket('channel_owner_transfer')
  onChannelOwnerTransfer(user: User) {
    this.$emit('transfer', user)
  }

  get itemComponent() {
    return ScrollItem
  }

  scrollToBotton() {
    for (let _ = 0; _ < 3; _++) {
      this.$nextTick(() => {
        const container = this.$refs.virtualMessageList as any

        if (container) {
          container.scrollToBottom()
        }
      })
    }
  }

  refresh() {
    this.$emit('refresh')
  }
}
</script>
