<template>
  <div>
    <v-btn :to="to('/auth/login')" color="primary"> Login </v-btn>
    <v-btn :to="to('/auth/register')" color="primary"> Register </v-btn>
  </div>
</template>

<script lang="ts">
import { computed, defineComponent, useRoute } from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const authStore = useAuthStore()
    const route = useRoute()

    const user = computed(() => authStore.user)

    const to = (path: string) => ({
      path,
      query: {
        from: route.value.fullPath,
      },
    })

    return {
      user,
      to,
    }
  },
})
</script>
