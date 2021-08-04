<template>
  <v-dialog v-model="dialog" max-width="600px">
    <template #activator="{ on, attrs }">
      <slot name="activator" :bind="attrs" :on="on" />
    </template>
    <v-card>
      <v-card-title>
        {{ $t('channel.invite.title', { name: channel.name }) }}
        <v-spacer />
        <button-close @click="dialog = false" />
      </v-card-title>
      <v-card-text>
        <v-autocomplete
          v-model="select"
          :loading="queryLoading !== 0"
          :disabled="loading"
          :items="items"
          :search-input.sync="search"
          clearable
          cache-items
          class="mx-4 mt-2"
          :error-messages="errors"
          flat
          hide-no-data
          :label="$t('channel.invite.label')"
          solo-inverted
          item-text="username"
          item-value="id"
        >
          <template #append-outer>
            <v-btn
              :loading="queryLoading !== 0 || loading"
              :disabled="!isSelected"
              large
              color="primary"
              height="48"
              class="ml-2"
              @click="submit()"
            >
              invite
            </v-btn>
          </template>
        </v-autocomplete>
      </v-card-text>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Prop, Vue, Watch } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, ChannelUser, User } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Array })
  users!: ChannelUser[]

  dialog = false

  queryLoading = 0
  loading = false
  error: any = null

  items: Array<User> = []
  search = null
  select: number | null = null

  @Watch('search')
  onSearchUpdate(val: string) {
    this.error = null

    this.querySelections(val)
  }

  get errors() {
    if (this.error) {
      return [
        this.error?.response?.data?.errors?.message ||
          'could not add this person',
      ]
    }

    return null
  }

  get isSelected() {
    return !!this.select
  }

  querySelections(query: string) {
    this.queryLoading++

    API.Search.users(query)
      .then((response) => {
        const already = this.users.map((x) => x.id)

        this.items = response.filter((x) => !already.includes(x.id))
      })
      .catch((error) => {
        this.$dialog.notify.error(`Could not search: ${error}`)
      })
      .then(() => this.queryLoading--)
  }

  async submit() {
    if (this.isSelected) {
      this.loading = true
      this.error = null

      try {
        const channelUser = await API.ChannelUsers.create(
          this.channel,
          this.select as number
        )

        this.$dialog.notify.success(
          `Successfully invited ${channelUser.username} to the channel`
        )

        this.select = null

        this.$emit('invited')
      } catch (error) {
        this.error = error
      }

      this.loading = false
    }
  }
}
</script>
