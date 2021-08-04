<template>
  <v-dialog
    v-model="dialog"
    fullscreen
    hide-overlay
    transition="dialog-bottom-transition"
  >
    <template #activator="{ on, attrs }">
      <slot name="activator" :bind="attrs" :on="on" />
    </template>
    <v-card color="black" class="forced-fullscreen">
      <v-card-title>
        {{ $t('channel.settings.title', { name: channel.name }) }}
        <v-spacer />
        <button-close @click="dialog = false" />
      </v-card-title>
      <v-row class="ma-2">
        <v-col v-if="isOwner || isSiteAdmin" cols="12">
          <channel-settings-card-edit :channel="channel" />
        </v-col>

        <v-col cols="12">
          <channel-settings-card-users
            :channel="channel"
            :users="users"
            :is-admin="isAdmin"
            :is-owner="isOwner"
            :is-site-admin="isSiteAdmin"
            :loading="loading"
            @refresh="$emit('refresh')"
          />
        </v-col>

        <v-col v-if="isOwner || isSiteAdmin" cols="12">
          <channel-settings-card-danger :channel="channel" />
        </v-col>
      </v-row>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel, ChannelUser } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Array })
  users!: ChannelUser[]

  @Prop({ type: Boolean, default: false })
  isOwner!: boolean

  @Prop({ type: Boolean, default: false })
  isAdmin!: boolean

  @Prop({ type: Boolean, default: false })
  isSiteAdmin!: boolean

  @Prop({ type: Boolean, default: false })
  loading!: boolean

  dialog = false
}
</script>

<style scoped>
  .forced-fullscreen {
    height: 100vh;
    overflow-y: scroll;
    overflow-x: hidden;
  }
</style>
