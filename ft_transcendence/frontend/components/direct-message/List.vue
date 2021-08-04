<template>
  <v-alert v-if="isEmpty" type="info" class="ma-4">
    You didn't contacted anyone
  </v-alert>
  <v-list v-else>
    <direct-message-item
      v-for="directMessage in directMessages"
      :key="directMessage.channel.id"
      :direct-message="directMessage"
    />
  </v-list>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { DirectMessage } from '~/models/DirectMessage'

@Component
export default class CompomentImpl extends Vue {
  @Prop({ type: Array, required: true })
  directMessages!: Array<DirectMessage>

  get isEmpty() {
    return !this.directMessages?.length
  }
}
</script>
