<template>
  <component :is="root" class="fill-height">
    <v-container fill-height fluid>
      <v-row class="fill-height" align="center">
        <v-col align="center">
          <slot />
        </v-col>
      </v-row>
    </v-container>
  </component>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Centered extends Vue {
  @Prop({ type: Boolean })
  plain!: boolean

  get root() {
    if (this.plain) {
      return 'div'
    }

    return 'v-main'
  }
}
</script>
