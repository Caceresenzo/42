<template>
  <v-list>
    <template v-for="(group, key) in groups">
      <template v-if="group.users.length">
        <v-subheader :key="key">
          {{ group.name }}
        </v-subheader>
        <div :key="`${key}-items`">
          <channel-user-item
            v-for="user in group.users"
            :key="user.id"
            :user="user"
            :channel="channel"
          />
        </div>
      </template>
    </template>
  </v-list>
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

  get groups() {
    return groupByTypes(
      (key) => this.$t(key) as string,
      this.users.filter((x) => !x.banned),
      this.channel
    )
  }
}
</script>
