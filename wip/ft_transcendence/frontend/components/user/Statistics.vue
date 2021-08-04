<template>
  <v-list>
    <template v-if="statistics != null">
      <user-statistics-list-item
        icon="mdi-crown"
        name="Win Count"
        :value="statistics.winCount"
      />
      <user-statistics-list-item
        icon="mdi-trophy-broken"
        name="Loss Count"
        :value="statistics.lossCount"
      />
    </template>
  </v-list>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { UserStatistics } from '~/models'

@Component
export default class Dot extends Vue {
  @Prop()
  statistics!: UserStatistics | null
}
</script>
