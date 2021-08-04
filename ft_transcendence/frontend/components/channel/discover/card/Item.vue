<template>
  <v-card link :to="to" @click="click()">
    <v-card-title>
      {{ channel.name }}
      <template v-if="!isAdmin && (isProtected || isPrivate)">
        <v-spacer />
        <channel-visibility-icon :channel="channel" />
        <channel-discover-dialog-unlock ref="unlock" :channel="channel" />
      </template>
    </v-card-title>
    <v-card-subtitle>{{ channel.owner.username }}</v-card-subtitle>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel, ChannelVisibility } from '~/models'
import { authStore } from '~/store'

@Component
export default class CompomentImpl extends Vue {
  @Prop()
  channel!: Channel

  get isAdmin() {
    return authStore.user!.admin
  }

  get isProtected() {
    return this.channel.visibility === ChannelVisibility.PROTECTED
  }

  get isPrivate() {
    return this.channel.visibility === ChannelVisibility.PRIVATE
  }

  get to() {
    if (!this.isAdmin && this.isProtected) {
      return null
    }

    return `/channels/${this.channel.id}`
  }

  click() {
    if (this.isProtected && !this.isAdmin) {
      ;(this.$refs.unlock as any)?.open()
    }
  }
}
</script>
