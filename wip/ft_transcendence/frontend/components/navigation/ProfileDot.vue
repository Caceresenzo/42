<template>
  <div class="d-block text-center mx-auto mt-4">
    <v-tooltip right>
      <template #activator="{ on, attr }">
        <v-btn icon large nuxt to="/profile" v-bind="attr" v-on="on">
          <user-avatar
            v-if="isAuthenticated"
            :user="user"
            :size="36"
            without-state
          />
        </v-btn>
      </template>

      <span>profile</span>
    </v-tooltip>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { authStore } from '~/store'

@Component
export default class Dot extends Vue {
  get user(): User | null {
    return authStore.user
  }

  get isAuthenticated(): boolean {
    return authStore.isAuthenticated
  }

  get picture(): string | null {
    return authStore.picture
  }
}
</script>
