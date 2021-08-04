<template>
  <v-list-item>
    <v-list-item-avatar>
      <v-icon>{{ icon }}</v-icon>
    </v-list-item-avatar>

    <v-list-item-content>
      <v-list-item-title>{{ name }}</v-list-item-title>
    </v-list-item-content>

    <v-list-item-icon>
      {{ value }}
    </v-list-item-icon>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Avatar extends Vue {
  @Prop({ type: String })
  icon!: string

  @Prop({ type: String })
  name!: string

  @Prop({ type: Number })
  value!: number
}
</script>
