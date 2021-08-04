<template>
  <v-container v-if="$fetchState.pending" fill-height fluid>
    <v-row align="center">
      <v-col align="center">
        <v-progress-circular indeterminate />
      </v-col>
    </v-row>
  </v-container>
  <page-error
    v-else-if="$fetchState.error"
    :error="$fetchState.error"
    @click="$fetch()"
  />
  <div v-else class="pa-4 fill-height" style="overflow-y: scroll">
    <v-app-bar app clipped-right>
      <v-toolbar-title>
        <drawer-menu />
        {{ $t('channel.discover._') }}
      </v-toolbar-title>
    </v-app-bar>

    <v-row v-if="notAddedChannels.length">
      <v-col
        v-for="channel in notAddedChannels"
        :key="channel.id"
        cols="12"
        md="6"
      >
        <channel-discover-card-item :channel="channel" />
      </v-col>
    </v-row>

    <v-row v-else align="center">
      <v-col align="center">
        <v-alert
          v-if="!addedChannels.length"
          type="info"
          style="max-width: 400px"
        >
          There is no channels available
          <v-btn class="mt-2" block small color="primary" to="/channels/create">
            why don't you create the first?
          </v-btn>
        </v-alert>

        <v-alert v-else type="info" style="max-width: 400px">
          You already joined all the existing channels
        </v-alert>
      </v-col>
    </v-row>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel } from '~/models'
import { channelsStore } from '~/store'

@Component
export default class Page extends Vue {
  channels: Channel[] = []

  get addedChannels(): Array<Channel> {
    return channelsStore.list
  }

  async fetch() {
    await this.$store.dispatch('channels/fetchAll')
    this.channels = await API.Channels.index()
  }

  get addedChannelIds() {
    return this.addedChannels.map((x) => x.id)
  }

  get notAddedChannels() {
    const addedChannelIds = this.addedChannelIds

    return this.channels.filter((x) => !addedChannelIds.includes(x.id))
  }
}
</script>
