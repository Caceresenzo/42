<template>
  <drawer-right v-model="drawerState">
    <channel-user-list :channel="channel" :users="users" />
    <template #append>
      <v-list>
        <v-list-item v-if="isAdmin">
          <channel-dialog-settings
            :channel="channel"
            :users="users"
            :is-admin="isAdmin"
            :is-owner="isOwner"
            :is-site-admin="isSiteAdmin"
            :loading="loading"
            @refresh="refresh"
          >
            <template #activator="{ on, attrs }">
              <v-btn block color="primary" v-bind="attrs" v-on="on">
                {{ $t('channel.settings.button') }}
                <v-icon right>mdi-cog</v-icon>
              </v-btn>
            </template>
          </channel-dialog-settings>
        </v-list-item>

        <v-list-item v-if="isAdmin">
          <channel-dialog-invite
            :channel="channel"
            :users="users"
            @invited="refresh"
          >
            <template #activator="{ on, attrs }">
              <v-btn block color="primary" v-bind="attrs" v-on="on">
                {{ $t('channel.invite.button') }}
                <v-icon right>mdi-account-plus</v-icon>
              </v-btn>
            </template>
          </channel-dialog-invite>
        </v-list-item>

        <v-list-item v-show="hasJoined && !isOwner">
          <channel-dialog-leave :channel="channel" @leaved="onLeaved()" />
        </v-list-item>

        <v-list-item v-if="isSiteAdmin && !hasJoined">
          <channel-join :channel="channel" @joined="onJoined" />
        </v-list-item>
      </v-list>
    </template>
  </drawer-right>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel, ChannelUser, ChannelVisibility } from '~/models'

@Component
export default class Index extends Vue {
  @Prop({ type: Boolean, default: true })
  value!: boolean

  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Array })
  users!: ChannelUser[]

  @Prop({ type: Boolean })
  hasJoined!: boolean

  @Prop({ type: Boolean })
  isSiteAdmin!: boolean

  @Prop({ type: Boolean, default: false })
  isOwner!: boolean

  @Prop({ type: Boolean, default: false })
  isAdmin!: boolean

  @Prop({ type: Boolean, default: false })
  loading!: boolean

  get drawerState(): boolean {
    return this.value
  }

  set drawerState(val) {
    this.$emit('input', val)
  }

  get toSettings() {
    const id = this.channel?.id

    if (id === undefined) {
      return null
    }

    return `/channels/${id}/settings`
  }

  onLeaved() {
    if (this.channel.visibility === ChannelVisibility.PUBLIC) {
      this.refresh()
    } else {
      this.$router.push({ path: '/channels' })
    }

    this.$emit('leaved')
  }

  onJoined() {
    this.$emit('joined')
  }

  refresh() {
    this.$emit('refresh')
  }
}
</script>
