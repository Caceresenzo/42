<template>
  <page-loading v-if="$fetchState.pending" />
  <page-error
    v-else-if="$fetchState.error"
    :error="$fetchState.error"
    @click="$fetch()"
  />
  <div v-else class="fill-height" style="overflow: auto">
    <v-toolbar v-if="smallScreen">
      <drawer-menu />
    </v-toolbar>

    <v-tabs v-model="tab" fixed-tabs>
      <v-tab v-for="{ category, icon } in tabs" :key="category">
        <v-icon left>mdi-{{ icon }}</v-icon>
        {{ $t(`relationship.tab.${category}._`) }}
      </v-tab>

      <v-tabs-items v-model="tab">
        <relationship-tab
          v-for="{ category, relationships } in tabs"
          :key="category"
          :category="category"
          :relationships="relationships"
        />
      </v-tabs-items>
    </v-tabs>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { Relationship, RelationshipType } from '~/models'
import { relationshipsStore, socketStore, uiStore } from '~/store'

@Component
export default class Page extends Vue {
  defaultTab = 1
  get tabs() {
    return [
      {
        category: 'online',
        icon: 'access-point',
        relationships: this.online,
      },
      {
        category: 'friends',
        icon: 'human-greeting',
        relationships: this.friends,
      },
      {
        category: 'pending',
        icon: 'motion-pause',
        relationships: this.pending,
      },
      {
        category: 'blocked',
        icon: 'block-helper',
        relationships: this.blocked,
      },
    ]
  }

  head() {
    return {
      title: 'Relationships',
    }
  }

  get smallScreen() {
    return uiStore.smallScreen
  }

  get friends() {
    return relationshipsStore.list.filter(
      (x) => x.type === RelationshipType.FRIEND
    )
  }

  get online() {
    const { connectedUserIds } = socketStore

    return this.friends.filter((x) => connectedUserIds.includes(x.peer.id))
  }

  get pending() {
    return relationshipsStore.list.filter(
      (x) =>
        x.type === RelationshipType.INCOMING ||
        x.type === RelationshipType.OUTCOMING
    )
  }

  get blocked() {
    return relationshipsStore.list.filter(
      (x) => x.type === RelationshipType.BLOCK
    )
  }

  async fetch() {
    await relationshipsStore.fetchAll()
  }

  get relationships(): Array<Relationship> {
    return relationshipsStore.list
  }

  get tab(): number {
    return parseInt((this.$route.query.tab || this.defaultTab) as string)
  }

  set tab(val: number) {
    this.$router
      .replace({
        query: {
          tab: `${val}` || undefined,
        },
      })
      .catch((_error) => ({}))
  }

  mounted() {
    if (this.online.length) {
      this.defaultTab = 0
    }
  }
}
</script>
