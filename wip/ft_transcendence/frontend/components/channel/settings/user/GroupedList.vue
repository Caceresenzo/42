<template>
  <v-list v-if="users.length" subheader>
    <v-subheader>{{ name }}</v-subheader>

    <channel-settings-user-grouped-list-row
      v-for="user in users"
      :key="user.id"
      :user="user"
      :channel="channel"
      :is-owner="isOwner"
      :is-admin="isAdmin"
      :is-site-admin="isSiteAdmin"
      @refresh="$emit('refresh')"
    />
  </v-list>
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

  @Prop({ type: String })
  name!: string

  @Prop({ type: Boolean })
  isOwner!: boolean

  @Prop({ type: Boolean })
  isAdmin!: boolean

  @Prop({ type: Boolean })
  isSiteAdmin!: boolean
}
</script>
