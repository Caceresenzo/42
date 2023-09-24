<template>
  <div />
</template>

<script lang="ts">
import {
  defineComponent,
  useContext,
  useFetch,
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const { $axios, $dialog } = useContext()
    const route = useRoute()
    const router = useRouter()
    const authStore = useAuthStore()

    useFetch(async () => {
      try {
        await $axios.$get('/api/auth/oauth/callback', {
          params: {
            code: route.value.query.code,
          },
        })

        await authStore.fetchUser()
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }

      router.replace('/')
    })

    return {}
  },
})
</script>
