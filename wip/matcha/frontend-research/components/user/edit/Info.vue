<template>
  <v-card>
    <v-card-title> Info </v-card-title>
    <v-card-text>
      <v-form id="info-form" @submit.prevent="submit">
        <v-text-field
          v-model="inputs.firstName"
          label="First Name"
          outlined
          dense
          :error-messages="validations.firstName"
        />
        <v-text-field
          v-model="inputs.lastName"
          label="Last Name"
          outlined
          dense
          :error-messages="validations.lastName"
        />
        <v-textarea
          v-model="inputs.biography"
          label="Biography"
          outlined
          dense
          :error-messages="validations.biography"
        />
        <v-select
          v-model="inputs.gender"
          label="Gender"
          outlined
          dense
          :items="genders"
          :error-messages="validations.gender"
        />
        <v-select
          v-model="inputs.sexualOrientation"
          label="Sexual Orientation"
          outlined
          dense
          :items="sexualOrientations"
          :error-messages="validations.sexualOrientation"
        />
      </v-form>
    </v-card-text>
    <v-card-actions>
      <v-spacer />
      <v-btn color="primary" form="info-form" type="submit" :loading="loading">
        save
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
import { Gender, SexualOrientation } from '~/models'
import { useAuthStore } from '~/store'
import { extractValidation } from '~/utils'
export default defineComponent({
  setup() {
    const { $dialog, $axios } = useContext()

    const authStore = useAuthStore()
    const loading = ref(false)

    const user = authStore.user
    const inputs = reactive({
      firstName: user?.firstName,
      lastName: user?.lastName,
      biography: user?.biography,
      gender: user?.gender,
      sexualOrientation: user?.sexualOrientation,
    })

    const validations = ref({})

    const submit = async () => {
      validations.value = extractValidation(null)

      try {
        loading.value = true

        authStore.user = await $axios.$patch(`/api/users/@me`, inputs)

        $dialog.notify.success('Saved!')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)

        validations.value = extractValidation(error)
      } finally {
        loading.value = false
      }
    }

    return {
      user,
      submit,
      inputs,
      validations,
      loading,
      genders: Object.keys(Gender),
      sexualOrientations: Object.keys(SexualOrientation),
    }
  },
})
</script>
