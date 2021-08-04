<template>
  <v-tab-item>
    <v-card flat>
      <v-card-title class="text-overline">
        {{ translatedCategory }} — {{ count }}
      </v-card-title>
      <v-list v-if="relationships.length">
        <component
          :is="itemImpl"
          v-for="relationship in relationships"
          :key="relationship.peer.id"
          :relationship="relationship"
        />
      </v-list>
      <v-card-text v-else class="text-center">
        {{ $t('relationship.nothing') }}
      </v-card-text>
    </v-card>
  </v-tab-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship } from '~/models'

const impls = {
  online: 'friend',
  friends: 'friend',
  pending: 'pending',
  blocked: 'blocked',
} as any

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  category!: string

  @Prop()
  relationships!: Array<Relationship>

  get count() {
    return this.relationships.length
  }

  get translatedCategory() {
    return this.$t(`relationship.tab.${this.category}.top`)
  }

  get itemImpl() {
    return `relationship-item-impl-${impls[this.category]}`
  }
}
</script>
