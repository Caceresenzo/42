<template>
  <direct-message-view-viewer :key="peerId" :peer-id="peerId" />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Page extends Vue {
  get peerId(): number {
    return parseInt(this.$route.params.peerid)
  }

  destroyed() {
    this.$socket.client.emit('channel_disconnect')
  }
}
</script>
