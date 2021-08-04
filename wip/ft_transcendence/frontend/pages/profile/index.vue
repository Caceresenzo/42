<template>
  <profile-page :user-id="id" />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { authStore } from '~/store'

@Component
export default class Page extends Vue {
  head() {
    return {
      title: 'Profile',
    }
  }

  get id(): number {
    return authStore.user!.id
  }
}
</script>
