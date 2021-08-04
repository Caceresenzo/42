<template>
  <v-row align="center" class="fill-height">
    <v-col align="center">
      <h1 style="color: red">{{ message }}</h1>
      <v-btn color="primary" @click="$emit('refresh')">refresh</v-btn>
    </v-col>
  </v-row>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Error extends Vue {
  @Prop()
  error!: any

  public get message() {
    return this.error?.message || 'failed to fetch'
  }
}
</script>
