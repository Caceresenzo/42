<template>
  <v-btn depressed block color="red" @click="click">
    {{ action }}
    <v-icon right>{{ icon }}</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Method } from 'axios'
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Relationship, RelationshipType, User } from '~/models'
import { relationshipsStore } from '~/store'

@Component
export default class Dot extends Vue {
  @Prop()
  user!: User

  @Prop()
  relationship!: Relationship

  get isBlocked(): boolean {
    return this.relationship?.type === RelationshipType.BLOCK
  }

  get action(): string {
    if (this.isBlocked) {
      return 'unblock'
    }

    return 'block'
  }

  get icon(): string {
    if (this.isBlocked) {
      return 'mdi-account-plus'
    }

    return 'mdi-account-cancel'
  }

  get dialogOptions(): {
    title: string
    text: string
    method: Method
    endpoint: string
    body?: any
    success: string
    error: (err: any) => string
  } {
    const { id, username } = this.user

    if (this.isBlocked) {
      return {
        title: `Unblock ${username}`,
        text: `Are you sure you want to unblock ${username}?`,
        method: `DELETE`,
        endpoint: `/users/@me/relationships/${id}`,
        body: undefined,
        success: `Successfully unblocked ${username}`,
        error: (err: any) => `Could not unblock ${username}: ${err}`,
      }
    }

    return {
      title: `Block ${username}`,
      text: `Are you sure you want to block ${username}? It will be removed from your friend list too.`,
      method: `POST`,
      endpoint: `/users/@me/relationships`,
      body: {
        peerId: this.user.id,
        type: 'block',
      },
      success: `Successfully blocked ${username}`,
      error: (err: any) => `Could not block ${username}: ${err}`,
    }
  }

  click() {
    const {
      title,
      text,
      method,
      endpoint,
      body,
      success,
      error,
      /* padding for the formatter... */
    } = this.dialogOptions

    this.$dialog.warning({
      title,
      text,
      actions: [
        {
          key: 'yes',
          text: 'Yes',
          color: 'error',
          handler: async () => {
            try {
              const response = await this.$axios.$request({
                url: endpoint,
                method,
                data: body,
              })

              if (method === 'DELETE') {
                relationshipsStore.deleteItem(this.user)
              } else {
                relationshipsStore.updateItem(response)
              }

              this.$dialog.notify.success(success)

              if (!this.$socket.connected) {
                this.$emit('refresh')
              }
            } catch (err) {
              this.$dialog.notify.error(
                error(err?.response?.data?.errors?.message || err)
              )
            }
          },
        },
        {
          key: 'cancel',
          text: 'Cancel',
        },
      ],
    })
  }
}
</script>
