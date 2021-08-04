<template>
  <v-btn outlined block color="red" :loading="loading" @click="submit">
    {{ text }}
    <v-icon right>mdi-{{ icon }}</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'

interface NextState {
  text: string
  icon: string
  title: string
  message: string
  success: string
  error: string
}

@Component
export default class Dot extends Vue {
  @Prop()
  user!: User

  loading = false

  get isBanned() {
    return this.user.banned
  }

  get state(): NextState {
    if (this.isBanned) {
      return {
        text: 'unban',
        icon: 'check',
        title: 'Unban confirmation',
        message: 'Are your sure that you want to unban this user?',
        success: 'Successfully unbanned',
        error: 'Could not unban',
      }
    }

    return {
      text: 'ban',
      icon: 'cancel',
      title: 'Ban confirmation',
      message: 'Are your sure that you want to ban this user?',
      success: 'Successfully banned',
      error: 'Could not ban',
    }
  }

  get text() {
    return this.state.text
  }

  get icon() {
    return this.state.icon
  }

  get title() {
    return this.state.title
  }

  get message() {
    return this.state.message
  }

  get success() {
    return this.state.success
  }

  get error() {
    return this.state.error
  }

  submit() {
    this.$dialog.warning({
      title: this.title,
      text: this.message,
      actions: [
        {
          key: 'yes',
          text: 'Yes',
          color: 'error',
          handler: async () => {
            if (this.loading) {
              return
            }

            this.loading = true

            try {
              await this.$axios.$post(`/users/${this.user.id}`, {
                banned: !this.isBanned,
              })

              this.$dialog.notify.success(this.success)

              this.$emit('refresh')
            } catch (error) {
              this.$dialog.notify.error(this.error)
            }

            this.loading = false
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
