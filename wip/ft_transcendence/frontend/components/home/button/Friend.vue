<template>
  <v-btn :to="to" class="ma-10" style="min-width: 200px">
    {{ text }}
    <v-icon dark right> mdi-human-greeting </v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { relationshipsStore } from '~/store'

@Component
export default class Friend extends Vue {
  get hasFriend() {
    return relationshipsStore.friends.length !== 0
  }

  get to() {
    if (this.hasFriend) {
      return '/direct-messages'
    }

    return '/users'
  }

  get text() {
    if (this.hasFriend) {
      return 'my friends'
    }

    return 'find new friends'
  }
}
</script>
