<template>
  <relationship-item-base :relationship="relationship">
    <template #icons>
      <v-btn icon :loading="loading" @click.prevent="unblock">
        <v-icon>mdi-account-remove</v-icon>
      </v-btn>
    </template>
  </relationship-item-base>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship } from '~/models'
import { relationshipsStore } from '~/store'

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  relationship!: Relationship

  loading = false

  async unblock() {
    if (this.loading) {
      return
    }

    this.loading = true

    try {
      const { peer } = this.relationship

      await this.$axios.$delete(`/users/@me/relationships/${peer.id}`)

      relationshipsStore.deleteItem(peer)
    } catch (error) {
      this.$dialog.notify.error(`Could not unblock: ${error}`)
    }

    this.loading = false
  }
}
</script>
