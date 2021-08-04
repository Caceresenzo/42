<template>
  <v-list>
    <v-list-item :to="to" :exact="exact">
      <v-list-item-avatar>
        <v-icon>{{ icon }}</v-icon>
      </v-list-item-avatar>
      <v-list-item-content>
        <v-list-item-title>{{ title }}</v-list-item-title>
      </v-list-item-content>
    </v-list-item>
  </v-list>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class TopItem extends Vue {
  @Prop()
  to!: string

  @Prop()
  param!: string

  @Prop()
  icon!: string

  @Prop()
  title!: string

  @Prop({ type: Boolean })
  alwaysExact!: boolean

  get exact() {
    if (this.alwaysExact) {
      return true
    }

    return this.$route.params[this.param] !== undefined
  }
}
</script>
