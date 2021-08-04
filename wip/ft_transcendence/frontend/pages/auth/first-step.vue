<template>
  <auth-first-step :user="user" />
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { authStore } from '~/store'

@Component({
  layout: 'empty',
})
export default class Page extends Vue {
  head() {
    return {
      title: 'First step',
    }
  }

  get user(): User | null {
    return authStore.user
  }
}
</script>
