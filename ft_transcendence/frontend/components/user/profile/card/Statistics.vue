<template>
  <v-card outlined :loading="loading">
    <v-card-title>
      Statistics
      <v-spacer />
      <v-btn icon :loading="loading" @click="refresh">
        <v-icon>mdi-refresh</v-icon>
      </v-btn>
    </v-card-title>
    <user-statistics :statistics="statistics" />
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User, UserStatistics } from '~/models'

@Component
export default class Dot extends Vue {
  @Prop()
  user!: User

  @Prop()
  statistics!: UserStatistics | null

  @Prop({ type: Boolean })
  loading!: boolean

  refresh() {
    this.$emit('refresh')
  }
}
</script>
