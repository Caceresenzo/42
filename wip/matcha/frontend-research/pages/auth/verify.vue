<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Verify </v-card-title>
          <v-card-text> Please verify your account! </v-card-text>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  onMounted,
  onUnmounted,
  ref,
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const route = useRoute()
    const router = useRouter()
    const authStore = useAuthStore()

    const from = computed(() => route.value.query.from as string)

    const interval = ref()
    onMounted(() => {
      interval.value = setInterval(async () => {
        const user = await authStore.fetchUser()

        if (!user) {
          router.push({
            path: '/auth/login',
            query: {
              from: from.value
            }
          })
        } else if (user.emailConfirmed) {
          router.push(from.value || '/')
        }
      }, 1000)
    })

    onUnmounted(() => {
      clearInterval(interval.value)
    })

    return {}
  },
})
</script>
