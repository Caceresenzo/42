<template>
  <v-list-item link :to="to">
    <v-list-item-avatar>
      <user-avatar :size="40" :user="peer" />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-list-item-title>{{ peer.username }}</v-list-item-title>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User, DirectMessage } from '~/models'

@Component
export default class CompomentImpl extends Vue {
  @Prop({ type: Object, required: true })
  directMessage!: DirectMessage

  get to() {
    return `/direct-messages/${this.directMessage.peer.id}`
  }

  get peer(): User {
    return this.directMessage.peer
  }
}
</script>
