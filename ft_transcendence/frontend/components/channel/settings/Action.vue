<template>
  <v-tooltip top v-bind="attr" v-on="on">
    <template #activator="{ on, attrs }">
      <v-btn
        icon
        :loading="loading"
        v-bind="attrs"
        @click="$emit('click')"
        v-on="on"
      >
        <v-icon color="primary"> {{ icon }} </v-icon>
      </v-btn>
    </template>
    <span>{{ tooltip }}</span>
  </v-tooltip>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Drawer extends Vue {
  @Prop({ type: String })
  icon!: string

  @Prop({ type: String })
  tooltip!: string

  @Prop({ type: Boolean, default: false })
  loading!: boolean

  @Prop()
  on!: any

  @Prop()
  attr!: any
}
</script>
