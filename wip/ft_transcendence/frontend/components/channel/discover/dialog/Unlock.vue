<template>
  <v-dialog v-model="dialog" max-width="600px">
    <v-card>
      <v-card-title>
        {{ $t('channel.discover.unlock.title', { name: channel.name }) }}
        <v-spacer />
        <button-close @click="dialog = false" />
      </v-card-title>
      <v-card-text>
        <v-text-field
          v-model="password"
          :loading="loading"
          clearable
          cache-items
          class="mx-4 mt-2"
          flat
          hide-no-data
          :label="$t('channel.discover.unlock.label')"
          solo-inverted
          item-text="username"
          item-value="id"
          type="password"
          :error-messages="errorMessage"
          autocomplete="new-password"
        >
          <template #append-outer>
            <v-btn
              :loading="loading"
              large
              color="primary"
              height="48"
              class="ml-2"
              @click="submit()"
            >
              unlock
            </v-btn>
          </template>
        </v-text-field>
      </v-card-text>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  dialog = false
  loading = false
  error: any = null

  get errorMessage() {
    if (!this.error) {
      return null
    }

    return [this.error?.response?.data?.errors?.message || 'could not unlock']
  }

  password: string | null = null

  open() {
    this.dialog = true
  }

  async submit() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    try {
      const channel = await API.Channels.unlock(this.channel, this.password)

      this.$emit('unlocked')

      this.$store.dispatch('channels/fetchAll')
      this.$router.push({ path: `/channels/${channel.id}` })
    } catch (error) {
      this.error = error
    }

    this.loading = false
  }
}
</script>
