<template>
  <v-dialog v-model="dialog" max-width="600px">
    <v-card>
      <v-card-title>
        {{ $t('channel.mute.title', { user: user.username }) }}
        <v-spacer />
        <button-close @click="dialog = false" />
      </v-card-title>
      <v-card-text>
        <v-select
          v-model="select"
          :disabled="loading"
          :items="items"
          clearable
          cache-items
          class="mx-4 mt-2"
          flat
          hide-no-data
          :label="$t('channel.invite.label')"
          solo-inverted
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
              {{ $t('channel.mute.button') }}
            </v-btn>
          </template>
        </v-select>
      </v-card-text>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import { Channel, ChannelUser } from '~/models'

@Component
export default class ComponentImpl extends Vue {
  @Prop({ type: Object })
  channel!: Channel

  @Prop({ type: Object })
  user!: ChannelUser

  dialog = false

  loading = false
  error: any = null

  search = null
  select: number | null = 300 /* 5 min */

  get items() {
    const duration = (key: string, seconds: number | null) => ({
      text: this.$t(`channel.mute.durations.${key}`),
      value: seconds,
    })

    return [
      duration('5m', 300),
      duration('15m', 900),
      duration('1h', 3600),
      duration('12h', 43200),
      duration('1d', 86400),
      duration('10d', 864000),
      duration('1M', 2628000),
      duration('1Y', 31536000),
      duration('indefinitely', null),
    ]
  }

  open() {
    this.dialog = true
  }

  close() {
    this.dialog = false
  }

  async submit() {
    if (this.loading) {
      return
    }

    this.loading = true
    this.error = null

    try {
      await API.ChannelUsers.mute(this.channel, this.user, this.select)

      this.$emit('muted')
      this.close()
    } catch (error) {
      this.error = error
    }

    this.loading = false
  }
}
</script>
