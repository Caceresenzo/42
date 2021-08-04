<template>
  <v-row align="center" class="fill-height">
    <v-col align="center">
      <h1>{{ message }}</h1>
      <v-progress-circular indeterminate />
      <slot />
    </v-col>
  </v-row>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Loading extends Vue {
  @Prop({ type: String })
  message!: string
}
</script>
