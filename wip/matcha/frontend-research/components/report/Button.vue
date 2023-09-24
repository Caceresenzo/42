<template>
  <v-btn :loading="loading" color="warning" @click="report"> Report </v-btn>
</template>

<script lang="ts">
import {
  defineComponent,
  PropType,
  ref,
  toRefs,
  useContext,
  useRouter,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { User } from '~/models'

export default defineComponent({
  props: {
    user: {
      type: Object as PropType<User>,
      required: true,
    },
  },
  setup(props) {
    const { user } = toRefs(props)
    const { $axios, $dialog } = useContext()
    const router = useRouter()

    const loading = ref(false)

    const report = async () => {
      const reason = await $dialog.prompt({
        title: 'Reason',
        type: 'warning',
      })

      if (!reason) {
        return
      }

      try {
        loading.value = true

        await $axios.$post('/api/reports', {
          userId: user.value.id,
          reason,
        })

        $dialog.notify.success('Reported!')
        router.push('/')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
      }
    }

    return {
      loading,
      report,
    }
  },
})
</script>
