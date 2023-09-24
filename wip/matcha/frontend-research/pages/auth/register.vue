<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Register </v-card-title>
          <v-card-text>
            <v-form id="form" @submit.prevent="register">
              <v-text-field
                v-model="inputs.login"
                label="Login"
                :error-messages="validations.login"
              />
              <v-text-field
                v-model="inputs.email"
                label="Email"
                type="email"
                :error-messages="validations.email"
              />
              <v-text-field
                v-model="inputs.firstName"
                label="First Name"
                :error-messages="validations.firstName"
              />
              <v-text-field
                v-model="inputs.lastName"
                label="Last Name"
                :error-messages="validations.lastName"
              />
              <v-text-field
                v-model="inputs.password"
                label="Password"
                type="password"
                :error-messages="validations.password"
              />
            </v-form>
          </v-card-text>
          <v-card-actions>
            <v-spacer />
            <v-btn type="submit" form="form"> Register </v-btn>
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
  unref,
  useContext,
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { extractValidation } from '~/utils'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const { $axios, $dialog } = useContext()

    const route = useRoute()
    const router = useRouter()
    const authStore = useAuthStore()

    const from = computed(() => route.value.query.from as string)

    const inputs = reactive({
      login: '',
      email: '',
      firstName: '',
      lastName: '',
      password: '',
    })

    const validations = ref({})

    const register = async () => {
      validations.value = extractValidation(null)

      try {
        await $axios.$post(`/api/auth/register`, unref(inputs))

        await authStore.fetchUser()

        router.push({
          path: '/auth/verify',
          query: {
            from: from.value,
          },
        })
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)

        validations.value = extractValidation(error)
      }
    }

    return {
      inputs,
      validations,
      register,
    }
  },
})
</script>
