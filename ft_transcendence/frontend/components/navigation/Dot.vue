<template>
  <div class="d-block text-center mx-auto mb-3">
    <v-tooltip right>
      <template #activator="{ on, attr }">
        <v-btn icon large nuxt :to="url" v-bind="attr" v-on="on">
          <v-icon> mdi-{{ icon }} </v-icon>
        </v-btn>
      </template>

      <span>{{ title }}</span>
    </v-tooltip>
  </div>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Dot extends Vue {
  @Prop({ type: String })
  icon!: string

  @Prop({ type: String })
  title!: string

  @Prop({ type: String })
  url!: string
}
</script>
