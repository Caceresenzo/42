<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Login </v-card-title>
          <v-card-text>
            <v-form id="form" @submit.prevent="login">
              <v-text-field v-model="inputs.login" label="Login" />
              <v-text-field
                v-model="inputs.password"
                label="Password"
                type="password"
              />
            </v-form>
          </v-card-text>
          <v-card-actions>
            <v-spacer />
            <v-btn type="submit" form="form"> Login </v-btn>
          </v-card-actions>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  defineComponent,
  onMounted,
  reactive,
  useRouter,
  watch,
} from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const router = useRouter()
    const authStore = useAuthStore()

    const inputs = reactive({
      login: '',
      password: '',
    })

    const login = async () => {
      await authStore.login(inputs.login, inputs.password)
    }

    watch(() => authStore.user, (user) => {
        if (user) {
            router.push("/")
        }
    }, { immediate: true })

    return {
      inputs,
      login,
    }
  },
})
</script>
