<template>
  <div>
    <channel-drawer
      :loading="$fetchState.pending"
      :error="$fetchState.error"
      :items="channels"
      :filterer="filterer"
      @refresh="$fetch"
    >
      <template #before>
        <channel-top-link />
      </template>

      <template #default="{ items }">
        <channel-list :channels="items" />
      </template>

      <template #append>
        <v-list>
          <v-list-item>
            <v-btn block color="primary" link to="/channels/create">
              {{ $t('channel.create.action') }}
              <v-icon right>mdi-plus</v-icon>
            </v-btn>
          </v-list-item>
        </v-list>
      </template>
    </channel-drawer>

    <v-main class="fill-height">
      <page-socket-not-connected v-if="!$socket.connected" />
      <nuxt-child v-else />
    </v-main>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { Channel } from '~/models'
import { channelsStore, uiStore } from '~/store'

@Component
export default class Page extends Vue {
  head() {
    return {
      title: 'Channels',
    }
  }

  async fetch() {
    await this.$store.dispatch('channels/fetchAll')
  }

  filterer(query: string, item: Channel) {
    if (!query?.length) {
      return true
    }

    return item.name.includes(query) || item.owner.username.includes(query)
  }

  get channels(): Array<Channel> {
    return channelsStore.list
  }

  mounted() {
    uiStore.setDrawer(true)
  }
}
</script>
