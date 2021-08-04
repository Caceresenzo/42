<template>
  <v-navigation-drawer
    v-model="state"
    app
    clipped
    fixed
    right
    style="height: 100%"
  >
    <slot />

    <template #append>
      <slot name="append" />
    </template>
  </v-navigation-drawer>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Right extends Vue {
  @Prop({ type: Boolean, default: true })
  value!: boolean

  get state(): boolean {
    return this.value
  }

  set state(val) {
    this.$emit('input', val)
  }
}
</script>
