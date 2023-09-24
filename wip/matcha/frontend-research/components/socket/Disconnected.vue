<template>
  <v-system-bar v-if="show" app color="error">
    <v-icon small>mdi-connection</v-icon>
    <b>Socket disconnected!</b>
 </v-system-bar>
</template>

<script lang="ts">
import { computed, defineComponent } from '@nuxtjs/composition-api'
import { useAuthStore, useSocketStore } from '~/store'
export default defineComponent({
  setup() {
    const authStore = useAuthStore()
    const socketStore = useSocketStore()

    const show = computed(() => authStore.logged && !socketStore.connected)

    return {
      show,
    }
  },
})
</script>
