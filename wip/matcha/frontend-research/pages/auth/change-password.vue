<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Change Password </v-card-title>
          <v-card-subtitle>
            You can close this page after changing your password.
          </v-card-subtitle>
          <v-card-text>
            <v-form id="info-form" @submit.prevent="submit">
              <v-text-field
                v-model="password"
                label="Password"
                type="password"
                outlined
                dense
              />
            </v-form>
          </v-card-text>
          <v-card-actions>
            <v-spacer />
            <v-btn
              color="primary"
              form="info-form"
              type="submit"
              :loading="loading"
            >
              change
            </v-btn>
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
  ref,
  useContext,
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
export default defineComponent({
  layout: 'empty',
  setup() {
    const { $axios, $dialog } = useContext()
    const router = useRouter()

    const route = useRoute()
    const token = computed(() => route.value.query.token)

    const loading = ref(false)
    const password = ref('')

    const submit = async () => {
      try {
        loading.value = true

        await $axios.post(`/api/auth/reset-password`, {
          token: token.value,
          password: password.value,
        })

        $dialog.notify.success('Password Changed!')
        router.push("/auth/login")
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      } finally {
        loading.value = false
      }
    }

    return {
      loading,
      password,
      submit,
    }
  },
})
</script>
