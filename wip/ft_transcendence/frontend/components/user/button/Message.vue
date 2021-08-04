<template>
  <v-btn depressed block color="primary" :to="to">
    message
    <v-icon right>mdi-message-arrow-right</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'

@Component
export default class Message extends Vue {
  @Prop()
  user!: User

  get to() {
    return `/direct-messages/${this.user.id}`
  }
}
</script>
