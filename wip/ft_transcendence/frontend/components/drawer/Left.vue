<template>
  <v-navigation-drawer
    v-model="drawer"
    width="300"
    class="mini-drawer-offset"
    fixed
    app
  >
    <template #prepend>
      <slot name="prepend" />
    </template>

    <slot />

    <template #append>
      <slot name="append" />
    </template>
  </v-navigation-drawer>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { uiStore } from '~/store'

@Component
export default class Left extends Vue {
  get drawer(): boolean {
    return uiStore.drawer
  }

  set drawer(val: boolean) {
    uiStore.setDrawer(val)
  }
}
</script>
