<template>
  <v-card>
    <v-card-text>
      <channel-settings-form-edit :initial="channel" />
    </v-card-text>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel } from '~/models'

@Component
export default class Edit extends Vue {
  @Prop({ type: Object })
  channel!: Channel
}
</script>
