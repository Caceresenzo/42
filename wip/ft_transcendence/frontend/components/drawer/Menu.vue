<template>
  <v-btn
    v-if="smallScreen"
    v-model="drawer"
    icon
    class="mr-2"
    @click="drawer = !drawer"
  >
    <v-icon>mdi-menu</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { uiStore } from '~/store'

@Component
export default class Menu extends Vue {
  get smallScreen() {
    return uiStore.smallScreen
  }

  get drawer(): boolean {
    return uiStore.drawer
  }

  set drawer(val: boolean) {
    uiStore.setDrawer(val)
  }
}
</script>
