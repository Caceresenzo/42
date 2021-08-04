<template>
  <v-btn
    :disabled="isDisabled"
    :text="isFriend"
    :outlined="isFriend"
    depressed
    block
    :color="color"
    @click="click"
  >
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

  get isFriend(): boolean {
    return this.relationship?.type === RelationshipType.FRIEND
  }

  get isBlocked(): boolean {
    return this.relationship?.type === RelationshipType.BLOCK
  }

  get isIncoming(): boolean {
    return this.relationship?.type === RelationshipType.INCOMING
  }

  get isOutcoming(): boolean {
    return this.relationship?.type === RelationshipType.OUTCOMING
  }

  get isDisabled() {
    return this.isOutcoming || this.isBlocked
  }

  get color() {
    if (this.isFriend) {
      return 'red'
    }

    return 'primary'
  }

  get action(): string {
    if (this.relationship) {
      if (this.isBlocked) {
        return 'blocked'
      }

      if (this.isFriend) {
        return 'unfriend'
      }

      if (this.isIncoming) {
        return 'accept'
      }

      if (this.isOutcoming) {
        return 'request sent'
      }
    }

    return 'friend'
  }

  get icon(): string {
    if (this.relationship && this.isFriend) {
      return 'mdi-account-remove'
    }

    return 'mdi-account-plus'
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

    if (this.relationship && !this.isIncoming) {
      return {
        title: `Remove ${username}`,
        text: `Are you sure you want to permanently remove ${username} from your friends?`,
        method: `DELETE`,
        endpoint: `/users/@me/relationships/${id}`,
        body: undefined,
        success: `Successfully removed ${username} from your friends`,
        error: (err: any) =>
          `Could not remove ${username} from your friends: ${err}`,
      }
    }

    const successVerb = this.isIncoming ? `accepted` : `sent`
    const errorAction = this.isIncoming ? `accept` : `request`

    return {
      title: `Add ${username}`,
      text: `Are you sure you want to add ${username} to your friends?`,
      method: `POST`,
      endpoint: `/users/@me/relationships`,
      body: {
        peerId: this.user.id,
        type: 'friend',
      },
      success: `Friendship request ${successVerb}`,
      error: (err: any) => `Could not ${errorAction} friendship: ${err}`,
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
