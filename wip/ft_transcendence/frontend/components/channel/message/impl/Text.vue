<template>
  <v-list-item style="align-items: unset">
    <v-list-item-avatar style="align-self: unset">
      <user-avatar :size="40" :user="message.user" without-state />
    </v-list-item-avatar>

    <v-list-item-content class="pt-2 break">
      <v-list-item-title>{{ message.user.username }}</v-list-item-title>
      <p class="text--secondary">{{ message.content }}</p>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { ChannelMessage } from '~/models'

@Component
export default class XText extends Vue {
  @Prop({ type: Object })
  message!: ChannelMessage
}
</script>

<style scoped>
  .break {
    word-break: break-all;
  }
</style>
