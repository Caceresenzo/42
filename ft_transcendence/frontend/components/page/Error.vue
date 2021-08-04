<template>
  <page-centered>
    <v-alert color="error">
      <slot :error="error" :message="message">
        <h2>{{ message }}</h2>
      </slot>
    </v-alert>
    <slot name="button">
      <v-btn color="primary" @click="$emit('click')">
        {{ $t('error.retry') }}
      </v-btn>
    </slot>
  </page-centered>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Loading extends Vue {
  @Prop()
  error!: Error

  get message(): string {
    return this.error?.message || 'error'
  }
}
</script>
