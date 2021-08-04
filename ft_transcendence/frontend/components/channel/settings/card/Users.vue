<template>
  <v-card :loading="loading">
    <v-card-title>
      Users
      <v-spacer />
      <channel-dialog-invite
        v-if="isAdmin || isSiteAdmin"
        :channel="channel"
        :users="users"
        @invited="$emit('refresh')"
      >
        <template #activator="{ on, attrs }">
          <v-btn icon v-bind="attrs" v-on="on">
            <v-icon>mdi-account-plus</v-icon>
          </v-btn>
        </template>
      </channel-dialog-invite>
      <v-btn icon :loading="loading" @click="$emit('refresh')">
        <v-icon>mdi-refresh</v-icon>
      </v-btn>
    </v-card-title>

    <channel-settings-user-grouped-list
      v-for="(group, key) in groups"
      :key="key"
      :is-owner="isOwner"
      :is-admin="isAdmin"
      :is-site-admin="isSiteAdmin"
      :channel="channel"
      :users="group.users"
      :name="group.name"
      @refresh="$emit('refresh')"
    />
  </v-card>
</template>

<script lang="ts">
import { groupByTypes } from '@/utils/groups'
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel, ChannelUser } from '~/models'

@Component
export default class Drawer extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Array })
  users!: Array<ChannelUser>

  @Prop({ type: Boolean })
  loading!: boolean

  @Prop({ type: Boolean, default: false })
  isOwner!: boolean

  @Prop({ type: Boolean, default: false })
  isAdmin!: boolean

  @Prop({ type: Boolean, default: false })
  isSiteAdmin!: boolean

  get groups() {
    return groupByTypes(
      (key) => this.$t(key) as string,
      this.users,
      this.channel
    )
  }
}
</script>
