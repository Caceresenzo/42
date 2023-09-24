<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Login </v-card-title>
          <v-card-subtitle>
            <router-link :to="{ path: '/auth/forgot-password', query: { from } }">
              Forgot password?
            </router-link>
          </v-card-subtitle>
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
            <v-btn to="/auth/oauth" color="secondary"> Login with Google </v-btn>
            <v-spacer />
            <v-btn type="submit" color="primary" form="form"> Login </v-btn>
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
  useRoute,
  useRouter,
  watch,
} from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const route = useRoute()
    const router = useRouter()
    const authStore = useAuthStore()

    const from = computed(() => route.value.query.from as string)

    const inputs = reactive({
      login: '',
      password: '',
    })

    const login = async () => {
      await authStore.login(inputs.login, inputs.password)
    }

    watch(
      () => authStore.user,
      (user) => {
        if (user) {
          router.push(from.value || '/')
        }
      },
      { immediate: true }
    )

    return {
      inputs,
      login,
      from,
    }
  },
})
</script>
