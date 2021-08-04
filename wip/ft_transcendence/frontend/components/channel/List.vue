<template>
  <v-alert v-if="isEmpty" type="info" class="ma-4">
    You didn't joined any channel
    <v-btn class="mt-2" block small color="primary" to="/channels" exact>
      discover
    </v-btn>
  </v-alert>
  <v-list v-else>
    <channel-item
      v-for="channel in channels"
      :key="channel.id"
      :channel="channel"
    />
  </v-list>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel } from '~/models'

@Component
export default class CompomentImpl extends Vue {
  @Prop()
  channels!: Channel[]

  get isEmpty() {
    return !this.channels?.length
  }
}
</script>
