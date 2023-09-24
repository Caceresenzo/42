<template>
  <div />
</template>

<script lang="ts">
import { defineComponent, useContext, useFetch } from '@nuxtjs/composition-api'
export default defineComponent({
  setup() {
    const { $axios } = useContext()

    useFetch(async () => {
      const url = await $axios.$get('/api/auth/oauth/url')
      window.location = url
    })

    return {}
  },
})
</script>
