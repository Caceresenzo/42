<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Logout </v-card-title>
          <v-card-text> Are you sure you want to logout? </v-card-text>
          <v-card-actions>
            <v-spacer />
            <v-btn :to="from || '/'"> Stay connected </v-btn>
            <v-btn @click="logout" color="primary"> Logout </v-btn>
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
  useRoute,
  useRouter,
} from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const route = useRoute()
    const router = useRouter()
    const authStore = useAuthStore()

    const from = computed(() => route.value.query.from)

    const logout = async () => {
      await authStore.logout()

      router.push('/')
    }

    return {
      logout,
      from,
    }
  },
})
</script>
