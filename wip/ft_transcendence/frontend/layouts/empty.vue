<template>
  <v-app dark :class="classes">
    <nuxt style="height: 100vh" />
  </v-app>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Empty extends Vue {
  get classes(): object {
    const isDark = this.$vuetify.theme.dark

    return {
      dark: isDark,
      light: !isDark,
    }
  }
}
</script>
