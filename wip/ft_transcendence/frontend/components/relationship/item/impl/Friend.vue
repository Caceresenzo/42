<template>
  <relationship-item-base :relationship="relationship">
    <template #icons>
      <v-btn icon link :to="to">
        <v-icon>mdi-message</v-icon>
      </v-btn>
    </template>
  </relationship-item-base>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  relationship!: Relationship

  get to() {
    return `/direct-messages/${this.relationship.peer.id}`
  }
}
</script>
