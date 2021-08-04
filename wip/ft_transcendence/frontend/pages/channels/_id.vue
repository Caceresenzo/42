<template>
  <channel-view-viewer :id="id" :key="id" />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Page extends Vue {
  get id(): number {
    return parseInt(this.$route.params.id)
  }

  destroyed() {
    this.$socket.client.emit('channel_disconnect')
  }
}
</script>
