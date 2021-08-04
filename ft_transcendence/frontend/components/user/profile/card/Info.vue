<template>
  <v-card class="pa-2" outlined>
    <v-row justify="center" align="center">
      <user-avatar
        :user="user"
        :size="128"
        :without-state="isMe"
        class="mt-8 mb-6"
      />
    </v-row>
    <v-card-title class="headline">
      <v-spacer />
      {{ user.username }}
      <v-spacer />
    </v-card-title>
    <v-col cols="12">
      <v-row justify="center" align="center">
        <v-col v-if="game" cols="12">
          <user-button-watch :game="game" />
        </v-col>
        <v-col v-if="isMe" cols="12">
          <user-button-settings />
        </v-col>
        <template v-else>
          <v-col cols="12">
            <direct-message-button-challenge
              never-small
              block
              :peer="user"
              @success="onChallenged"
            />
          </v-col>
          <v-col cols="12" xl="6">
            <user-button-friend
              :user="user"
              :relationship="relationship"
              @refresh="refresh"
            />
          </v-col>
          <v-col cols="12" xl="6">
            <user-button-block
              :user="user"
              :relationship="relationship"
              @refresh="refresh"
            />
          </v-col>
          <v-col cols="12">
            <user-button-message :user="user" />
          </v-col>
          <v-col v-if="selfIsSiteAdmin && !isAdmin" cols="12">
            <user-button-ban :user="user" @refresh="refresh" />
          </v-col>
        </template>
      </v-row>
    </v-col>
  </v-card>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship, User } from '~/models'
import { Game } from '~/models/Game'
import { authStore, relationshipsStore } from '~/store'

@Component
export default class Info extends Vue {
  @Prop()
  user!: User

  @Prop()
  game!: Game | null

  get relationship(): Relationship | null {
    const { id } = this.user

    return relationshipsStore.list.find((x) => x.peer.id === id) || null
  }

  get isMe() {
    return authStore.user!.id === this.user.id
  }

  get isAdmin() {
    return this.user.admin
  }

  get selfIsSiteAdmin() {
    return authStore.user!.admin
  }

  refresh() {
    this.$emit('refresh')
  }

  onChallenged() {
    this.$router.push({
      path: `/direct-messages/${this.user.id}`,
    })
  }
}
</script>
