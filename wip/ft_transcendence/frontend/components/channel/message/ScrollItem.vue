<template>
  <channel-message-item :message="source" />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

import { ChannelMessage } from '~/models'

@Component
export default class ScrollItem extends Vue {
  @Prop({ type: Number })
  index!: number

  @Prop({ type: Object })
  source!: ChannelMessage
}
</script>
