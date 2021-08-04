<template>
  <page-centered :plain="plain">
    <v-icon :class="iconClass" size="128" :color="color">{{ icon }}</v-icon>
    <v-card-text v-if="text"> {{ text }} </v-card-text>
  </page-centered>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class CenteredIcon extends Vue {
  @Prop({ type: Boolean })
  plain!: boolean

  @Prop({ type: String })
  text!: string

  @Prop({ type: String })
  icon!: string

  @Prop()
  iconClass!: any

  @Prop({ type: String })
  color!: string
}
</script>
