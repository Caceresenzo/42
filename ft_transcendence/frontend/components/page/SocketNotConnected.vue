<template>
  <page-centered-icon
    plain
    text="socket not connected"
    icon="mdi-power-plug-off"
    color="red"
  />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class SocketNotConnected extends Vue {}
</script>
