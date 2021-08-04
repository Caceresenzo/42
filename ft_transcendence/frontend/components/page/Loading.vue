<template>
  <page-centered>
    <h1 v-if="title">{{ title }}</h1>
    <v-progress-circular indeterminate />
    <slot />
  </page-centered>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Loading extends Vue {
  @Prop()
  title!: string | null
}
</script>
