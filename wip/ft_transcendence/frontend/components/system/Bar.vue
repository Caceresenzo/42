<template>
  <v-system-bar app>
    <v-menu open-on-hover bottom offset-y>
      <template #activator="{ on, attrs }">
        <div v-bind="attrs" v-on="on">ft-transcendence</div>
      </template>

      <v-list>
        <v-subheader> made by </v-subheader>

        <author-item
          v-for="author in authors"
          :key="author.login"
          :author="author"
        />
      </v-list>
    </v-menu>
    <v-spacer />
    <template v-if="$socket.connected">
      {{ connectedCount }}
      <v-icon>mdi-account-group</v-icon>
      <v-icon color="green">mdi-power-plug</v-icon>
    </template>
    <v-icon v-else color="red">mdi-power-plug-off</v-icon>
  </v-system-bar>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { Author } from '~/models'
import { socketStore } from '~/store'

@Component
export default class Bar extends Vue {
  authors: Array<Author> = [
    {
      name: 'Alice TETU',
      login: 'atetu',
      tasks: ['game', 'socket'],
    },
    {
      name: 'Badria MELLOUK',
      login: 'bmellouk',
      tasks: ['relationship', 'user profile'],
    },
    {
      name: 'Enzo CACERES',
      login: 'ecaceres',
      tasks: ['channel', 'authentication'],
    },
  ]

  get connectedCount() {
    return socketStore.connectedUserIds.length
  }
}
</script>
