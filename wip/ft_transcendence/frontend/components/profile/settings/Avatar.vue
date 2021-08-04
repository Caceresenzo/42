<template>
  <v-list-item>
    <v-list-item-avatar size="128">
      <user-avatar :user="user" :src="url" :size="128" without-state />
    </v-list-item-avatar>
    <v-list-item-content>
      <v-file-input
        v-model="image"
        :loading="loading"
        :error-messages="error"
        label="Select an image file"
        hide-details="auto"
        accept="image/*"
        @change="preview"
      />
    </v-list-item-content>
    <v-list-item-icon style="height: 128px; align-items: center">
      <v-btn v-show="url" :loading="loading" color="primary" @click="upload()">
        <v-icon left>mdi-upload</v-icon>
        upload
      </v-btn>
    </v-list-item-icon>
  </v-list-item>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { authStore } from '~/store'

@Component
export default class Avatar extends Vue {
  image: File | null = null
  url: string | null = null
  loading = false
  error: any = null

  preview(file: File) {
    if (file) {
      this.url = URL.createObjectURL(file)
    } else {
      this.url = null
    }
  }

  async upload() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    try {
      const formData = new FormData()
      formData.append('image', this.image as File)

      await this.$axios.post(`/users/@me/profile/avatar`, formData)
      await authStore.fetch()

      this.$dialog.notify.success('Successfully uploaded')
    } catch (error) {
      this.error = error.response?.data?.errors?.message || 'unknown error'

      this.$dialog.notify.error('Could not upload')
    }

    this.loading = false
  }

  get user(): User | null {
    return authStore.user
  }
}
</script>
