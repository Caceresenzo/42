<template>
  <v-btn
    v-if="logged && liked"
    :loading="loading"
    color="warning"
    @click="unlike"
  >
    Unlike
  </v-btn>
  <v-btn
    v-else-if="logged && !liked"
    :loading="loading"
    color="success"
    @click="like"
  >
    Like
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

interface LikeStatus {
  liked: boolean
  likedAt: string
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

    const status = ref<LikeStatus>()
    const loading = ref(false)

    const logged = computed(() => authStore.logged)
    const liked = computed(() => status.value?.liked ?? false)

    const endpoint = computed(() => `/api/likes/${peer.value.id}`)

    const { fetch } = useFetch(async () => {
      if (logged.value) {
        status.value = await $axios.$get(endpoint.value)
      } else {
        status.value = undefined
      }
    })

    watch(logged, fetch)

    const like = async () => {
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

    const unlike = async () => {
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
      liked,
      like,
      unlike,
    }
  },
})
</script>
