<template>
  <v-text-field
    ref="input"
    v-model="content"
    solo-inverted
    hide-details
    autofocus
    :loading="loading"
    :readonly="loading"
    @keydown.enter="send"
  />
</template>

<script lang="ts">
import {
  defineComponent,
  nextTick,
  PropType,
  ref,
  useContext,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { User } from '~/models'
import { useAuthStore } from '~/store'

export default defineComponent({
  props: {
    peer: {
      type: Object as PropType<User>,
      required: true,
    },
  },
  setup(props) {
    const { $axios, $dialog } = useContext()
    const authStore = useAuthStore()

    const input = ref<HTMLInputElement>()

    const loading = ref(false)
    const content = ref('')
    const send = async () => {
      if (!content.value) {
        return
      }

      try {
        loading.value = true

        await $axios.$post('/api/messages', {
          content: content.value,
          peerId: props.peer.id,
        })

        content.value = ''
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
        nextTick(() => {
            input.value?.focus()
        })
      }
    }

    return {
      content,
      send,
      loading,
      input,
    }
  },
})
</script>
