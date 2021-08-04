<template>
  <page-loading title="logging out..." />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { authStore } from '~/store'

@Component
export default class Logout extends Vue {
  head() {
    return {
      title: 'Logout',
    }
  }

  mounted() {
    setTimeout(() => {
      this.logout()
      this.$router.push('/auth')
    }, 200)
  }

  logout() {
    authStore.logout()
  }
}
</script>
