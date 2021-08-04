<template>
  <v-list-item link :to="to">
    <v-list-item-avatar size="40">
      <user-avatar :user="user" :size="40" />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-list-item-title>
        {{ user.username }}
      </v-list-item-title>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'

@Component
export default class Item extends Vue {
  @Prop()
  user!: User

  get to() {
    return `/users/${this.user.id}`
  }
}
</script>
