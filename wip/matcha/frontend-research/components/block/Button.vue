<template>
  <v-btn
    v-if="logged && blocked"
    :loading="loading"
    color="warning"
    @click="unblock"
  >
    Unblock
  </v-btn>
  <v-btn
    v-else-if="logged && !blocked"
    :loading="loading"
    color="success"
    @click="block"
  >
    Block
  </v-btn>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  PropType,
  ref,
  toRefs,
  useContext,
  useFetch,
  watch,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { User } from '~/models'
import { useAuthStore } from '~/store'

interface BlockStatus {
  blocked: boolean
  blockedAt: string
}

export default defineComponent({
  props: {
    peer: {
      type: Object as PropType<User>,
      required: true,
    },
  },
  setup(props) {
    const { peer } = toRefs(props)
    const { $axios, $dialog } = useContext()
    const authStore = useAuthStore()

    const status = ref<BlockStatus>()
    const loading = ref(false)

    const logged = computed(() => authStore.logged)
    const blocked = computed(() => status.value?.blocked ?? false)

    const endpoint = computed(() => `/api/blocks/${peer.value.id}`)

    const { fetch } = useFetch(async () => {
      if (logged.value) {
        status.value = await $axios.$get(endpoint.value)
      } else {
        status.value = undefined
      }
    })

    watch(logged, fetch)

    const block = async () => {
      try {
        loading.value = true
        status.value = await $axios.$post(endpoint.value)
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
      }
    }

    const unblock = async () => {
      try {
        loading.value = true
        status.value = await $axios.$delete(endpoint.value)
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
      }
    }

    return {
      loading,
      logged,
      blocked,
      block,
      unblock,
    }
  },
})
</script>
