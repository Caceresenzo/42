<template>
  <v-card>
    <v-card-title> Change Email </v-card-title>
    <v-card-text>
      <v-form id="email-form" @submit.prevent="submit">
        <v-text-field
          v-model="inputs.newEmail"
          label="New Email"
          outlined
          dense
          :error-messages="validations.newEmail"
          type="email"
        />
      </v-form>
    </v-card-text>
    <v-card-actions>
      <v-spacer />
      <v-btn color="primary" form="email-form" type="submit" :loading="loading">
        change
      </v-btn>
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import {
  defineComponent,
  reactive,
  ref,
  useContext,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { useAuthStore } from '~/store'
import { extractValidation } from '~/utils'
export default defineComponent({
  setup() {
    const { $dialog, $axios } = useContext()

    const loading = ref(false)
    const authStore = useAuthStore()

    const user = authStore.user
    const inputs = reactive({
      newEmail: user?.email
    })

    const validations = ref({})

    const submit = async () => {
      validations.value = extractValidation(null)

      try {
        loading.value = true

        await $axios.$post(`/api/auth/change-email`, inputs)

        $dialog.notify.success('Email sent!')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)

        validations.value = extractValidation(error)
      } finally {
        loading.value = false
      }
    }

    return {
      submit,
      inputs,
      validations,
      loading,
    }
  },
})
</script>
