<template>
  <div v-if="user">
    <nuxt-child :key="userId" :user="user" />
  </div>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  ref,
  useContext,
  useFetch,
  watch,
} from '@nuxtjs/composition-api'
import { usePathValue } from '~/composables'
import { User } from '~/models'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const { $axios } = useContext()
    const authStore = useAuthStore()

    const user = ref<User>()
    const userId = usePathValue<string>('id')

    const resolvedUserId = computed(() => {
      if (userId.value === '@me' && authStore.logged) {
        return authStore.user?.id || userId.value
      }

      return userId.value
    })

    const { fetch } = useFetch(async () => {
      user.value = await $axios.$get(`/api/users/${resolvedUserId.value}`)
    })

    watch(userId, fetch)

    return {
      user,
      userId,
    }
  },
})
</script>
