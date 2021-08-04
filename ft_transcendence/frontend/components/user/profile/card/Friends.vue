<template>
  <v-card outlined :loading="loading">
    <v-card-title>
      Friends
      <v-spacer />
      <v-btn icon :loading="loading" @click="refresh">
        <v-icon>mdi-refresh</v-icon>
      </v-btn>
    </v-card-title>
    <v-list>
      <user-friend-empty v-if="!last.length" />
      <user-friend-item
        v-for="{ peer: user } in last"
        :key="user.id"
        :user="user"
      />
    </v-list>
    <v-card-text v-if="hasMoreThan" class="text-right">
      and {{ xMore }} more
    </v-card-text>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship, User } from '~/models'

const size = 5

@Component
export default class Friends extends Vue {
  @Prop()
  user!: User

  @Prop()
  friends!: Array<Relationship>

  @Prop({ type: Boolean })
  loading!: boolean

  refresh() {
    this.$emit('refresh')
  }

  get last() {
    return this.friends.slice(-size)
  }

  get hasMoreThan() {
    return this.friends.length > size
  }

  get xMore() {
    return this.friends.length - size
  }
}
</script>
