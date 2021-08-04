<template>
  <v-list-item>
    <v-list-item-avatar>
      <user-avatar :user="user" :size="40" />
    </v-list-item-avatar>

    <v-list-item-content>
      <v-list-item-title>{{ user.username }}</v-list-item-title>
      <template v-if="user.muted">
        <v-list-item-subtitle v-if="user.mutedUntil">
          muted until {{ user.mutedUntil }}
        </v-list-item-subtitle>
        <v-list-item-subtitle v-else>muted infinitly</v-list-item-subtitle>
      </template>
    </v-list-item-content>

    <v-list-item-icon>
      <template v-if="isOwner || isSiteAdmin">
        <channel-settings-action
          v-if="!isChannelOwner"
          icon="mdi-swap-horizontal-bold"
          tooltip="transfer ownership"
          @click="transferOwnership()"
        />

        <template v-if="!isSelf">
          <channel-settings-action
            v-if="user.admin"
            icon="mdi-arrow-down-bold"
            tooltip="demote"
            @click="demote()"
          />
          <channel-settings-action
            v-else
            icon="mdi-arrow-up-bold"
            tooltip="promote"
            @click="promote()"
          />
        </template>
      </template>

      <template v-if="isAdmin || isSiteAdmin">
        <channel-settings-action
          v-if="user.muted"
          icon="mdi-volume-mute"
          tooltip="unmute"
          @click="unmute()"
        />
        <template v-else>
          <channel-settings-action
            icon="mdi-volume-plus"
            tooltip="mute"
            @click="openMuteDialog()"
          />
          <channel-dialog-mute
            ref="muteDialog"
            :channel="channel"
            :user="user"
            @muted="$emit('refresh')"
          />
        </template>

        <template v-if="!isSelf && !isChannelOwner">
          <channel-settings-action
            v-if="user.banned"
            icon="mdi-check"
            tooltip="unban"
            @click="unban()"
          />
          <channel-settings-action
            v-else
            icon="mdi-cancel"
            tooltip="ban"
            @click="ban()"
          />
        </template>

        <channel-settings-action
          v-if="!isChannelOwner"
          icon="mdi-logout-variant"
          tooltip="kick"
          @click="kick()"
        />
      </template>
    </v-list-item-icon>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, ChannelUser } from '~/models'
import { authStore } from '~/store'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Object })
  user!: ChannelUser

  @Prop({ type: Boolean })
  isOwner!: boolean

  @Prop({ type: Boolean })
  isAdmin!: boolean

  @Prop({ type: Boolean })
  isSiteAdmin!: boolean

  get isChannelOwner() {
    return this.channel.owner.id === this.user.id
  }

  get isSelf() {
    return this.user.id === authStore.user!.id
  }

  confirmAction(i18nKey: string, onYes: () => Promise<void>) {
    this.$confirm(
      this.$t(i18nKey, { user: this.user.username }) as string
    ).then(async (response) => {
      if (response) {
        try {
          await onYes()

          this.$emit('refresh')
        } catch (error) {
          this.$dialog.notify.error(`Failed: ${error}`)
        }
      }
    })
  }

  transferOwnership() {
    this.confirmAction('channel.action.transfer', async () => {
      await API.ChannelUsers.transfer(this.channel, this.user)
    })
  }

  promote() {
    this.confirmAction('channel.action.promote', async () => {
      await API.ChannelUsers.promote(this.channel, this.user)
    })
  }

  demote() {
    this.confirmAction('channel.action.demote', async () => {
      await API.ChannelUsers.demote(this.channel, this.user)
    })
  }

  ban() {
    this.confirmAction('channel.action.ban', async () => {
      await API.ChannelUsers.ban(this.channel, this.user)
    })
  }

  unban() {
    this.confirmAction('channel.action.unban', async () => {
      await API.ChannelUsers.unban(this.channel, this.user)
    })
  }

  openMuteDialog() {
    const dialog: any = this.$refs.muteDialog

    dialog.open()
  }

  unmute() {
    this.confirmAction('channel.action.unmute', async () => {
      await API.ChannelUsers.unmute(this.channel, this.user)
    })
  }

  kick() {
    this.confirmAction('channel.action.kick', async () => {
      await API.ChannelUsers.destroy(this.channel, this.user)
    })
  }
}
</script>
