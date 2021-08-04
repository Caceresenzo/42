<template>
  <v-main class="fill-height">
    <page-socket-not-connected v-if="!$socket.connected" />
    <nuxt-child v-else />
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Page extends Vue {
  head() {
    return {
      title: 'Games',
    }
  }
}
</script>
