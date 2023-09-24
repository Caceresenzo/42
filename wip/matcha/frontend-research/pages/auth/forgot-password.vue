<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card :loading="loading">
          <v-card-title> Forgot Password </v-card-title>
          <v-card-text>
            <v-form id="form" @submit.prevent="forgot">
              <v-text-field v-model="inputs.email" label="Email" type="email" />
            </v-form>
          </v-card-text>
          <v-card-actions>
            <v-spacer />
            <v-btn type="submit" form="form" :loading="loading"> Submit </v-btn>
          </v-card-actions>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  reactive,
  ref,
  useContext,
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
export default defineComponent({
  setup() {
    const route = useRoute()
    const router = useRouter()
    const { $axios, $dialog } = useContext()

    const from = computed(() => route.value.query.from as string)

    const loading = ref(false)
    const inputs = reactive({
      email: '',
    })

    const forgot = async () => {
      try {
        loading.value = true

        await $axios.post('/api/auth/forgot-password', inputs)

        $dialog.notify.success(
          'An email will be sent if there is an account with this email.'
        )

        router.push(from.value || '/')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
      }
    }

    return {
      inputs,
      forgot,
      loading,
    }
  },
})
</script>
