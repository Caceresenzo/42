<template>
  <v-card>
    <v-card-title> Change Password </v-card-title>
    <v-card-text>
      <v-form id="password-form" @submit.prevent="submit">
        <v-text-field
          v-model="inputs.oldPassword"
          label="Old Password"
          outlined
          dense
          :error-messages="validations.oldPassword"
          type="password"
        />
        <v-text-field
          v-model="inputs.newPassword"
          label="New Password"
          outlined
          dense
          :error-messages="validations.newPassword"
          type="password"
        />
        <v-text-field
          v-model="inputs.confirmPassword"
          label="Confirm Password"
          outlined
          dense
          :error-messages="validations.confirmPassword"
          type="password"
        />
      </v-form>
    </v-card-text>
    <v-card-actions>
      <v-spacer />
      <v-btn color="primary" form="password-form" type="submit" :loading="loading">
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
import { extractValidation } from '~/utils'
export default defineComponent({
  setup() {
    const { $dialog, $axios } = useContext()

    const loading = ref(false)

    const inputs = reactive({
      oldPassword: "",
      newPassword: "",
      confirmPassword: "",
    })

    const validations = ref({})

    const submit = async () => {
      validations.value = extractValidation(null)

      try {
        loading.value = true

        await $axios.$post(`/api/auth/change-password`, inputs)

        $dialog.notify.success('Updated!')

        inputs.oldPassword = ""
        inputs.newPassword = ""
        inputs.confirmPassword = ""
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
