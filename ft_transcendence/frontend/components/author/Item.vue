<template>
  <v-list-item :href="to" target="_blank">
    <v-list-item-avatar>
      <v-img :src="picture" />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-list-item-title>
        {{ author.name }}
      </v-list-item-title>
      <v-list-item-subtitle>
        <v-chip
          v-for="task in author.tasks"
          :key="task"
          color="primary"
          class="mr-2"
          x-small
        >
          {{ task }}
        </v-chip>
      </v-list-item-subtitle>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Author } from '~/models'

@Component
export default class Bar extends Vue {
  @Prop()
  author!: Author

  get picture() {
    return `https://cdn.intra.42.fr/users/small_${this.author.login}.jpg`
  }

  get to() {
    return `https://profile.intra.42.fr/users/${this.author.login}`
  }
}
</script>
