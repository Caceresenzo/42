<template>
  <v-main class="fill-height">
    <v-row class="ma-4">
      <v-col cols="12">
        <v-card>
          <v-card-title>Security</v-card-title>
          <v-card-text>
            <v-form>
              <profile-settings-2-factor />
            </v-form>
          </v-card-text>
        </v-card>
      </v-col>
      <v-col cols="12">
        <v-card>
          <v-card-title>Avatar</v-card-title>
          <v-card-text>
            <v-form>
              <profile-settings-avatar />
            </v-form>
          </v-card-text>
        </v-card>
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Page extends Vue {
  head() {
    return {
      title: 'Settings',
    }
  }
}
</script>
