<template>
  <v-card-text class="text-center">
    could not fetch achievements
    <a href="javascript:void" @click="retry">retry</a>
  </v-card-text>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class ComponentImpl extends Vue {
  retry() {
    this.$emit('retry')
  }
}
</script>
