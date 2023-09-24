<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> New Email </v-card-title>
          <v-card-subtitle> Your email will be changed shortly. You can close this page. </v-card-subtitle>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  useContext,
  useFetch,
  useRoute,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
export default defineComponent({
  layout: "empty",
  setup() {
    const { $axios, $dialog } = useContext()

    const route = useRoute()
    const token = computed(() => route.value.query.token)

    useFetch(async () => {
      try {
        await $axios.$post(
          '/api/auth/confirm-new-email',
          {
            token: token.value,
          }
        )
        
        $dialog.notify.success("Email changed!")
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }
    })

    return {}
  },
})
</script>
