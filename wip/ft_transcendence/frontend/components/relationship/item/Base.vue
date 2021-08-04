<template>
  <v-list-item link :to="to">
    <v-list-item-avatar size="60">
      <user-avatar :user="user" />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-list-item-title>
        {{ user.username }}
      </v-list-item-title>
    </v-list-item-content>
    <v-list-item-icon>
      <slot name="icons" />
    </v-list-item-icon>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  relationship!: Relationship

  get user() {
    return this.relationship.peer
  }

  get to() {
    return `/users/${this.user.id}`
  }
}
</script>
