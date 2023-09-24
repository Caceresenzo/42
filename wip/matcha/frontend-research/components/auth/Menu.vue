<template>
  <v-menu offset-y>
    <template #activator="{ on, attrs }">
      <v-btn color="primary" dark v-bind="attrs" v-on="on">
        {{ user.login }}
      </v-btn>
    </template>
    <v-list>
      <v-list-item :to="`/users/@me`">
        <v-list-item-action>
          <v-icon>mdi-account</v-icon>
        </v-list-item-action>
        <v-list-item-title> My profile </v-list-item-title>
      </v-list-item>
      <v-divider />
      <v-list-item :to="toLogout">
        <v-list-item-action>
          <v-icon>mdi-logout</v-icon>
        </v-list-item-action>
        <v-list-item-title> Logout </v-list-item-title>
      </v-list-item>
    </v-list>
  </v-menu>
</template>

<script lang="ts">
import { computed, defineComponent, useRoute } from '@nuxtjs/composition-api'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const authStore = useAuthStore()
    const route = useRoute()

    const user = computed(() => authStore.user)

    const toLogout = computed(() => ({
      path: '/auth/logout',
      query: {
        from: route.value.fullPath,
      },
    }))

    return {
      user,
      toLogout,
    }
  },
})
</script>
