<template>
  <v-list-item v-if="hidden && !display" style="align-self: unset">
    <v-list-item-avatar style="align-self: unset">
      <v-tooltip left>
        <template #activator="{ on, attrs }">
          <v-btn icon v-bind="attrs" @click="unlock" v-on="on">
            <v-icon>mdi-lock-question</v-icon>
          </v-btn>
        </template>
        <span>Click to see anyway</span>
      </v-tooltip>
    </v-list-item-avatar>
    <v-list-item-content class="pt-2">
      <v-list-item-title>Hidden message</v-list-item-title>
    </v-list-item-content>
  </v-list-item>
  <component :is="componentImpl" v-else :message="message" />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

import { ChannelMessage } from '~/models'
import { relationshipsStore } from '~/store'

@Component
export default class Item extends Vue {
  @Prop({ type: Object })
  message!: ChannelMessage

  display = false

  get hidden(): boolean {
    return relationshipsStore.blockedPeerIds.includes(this.message.user.id)
  }

  unlock() {
    this.display = true
  }

  mounted() {
    this.display = !this.hidden
  }

  get componentImpl() {
    return `channel-message-impl-${this.message.type}`
  }
}
</script>

<style scoped>
  .break {
    word-break: break-all;
  }
</style>
