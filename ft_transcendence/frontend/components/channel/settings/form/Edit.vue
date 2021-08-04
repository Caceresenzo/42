<template>
  <v-form ref="form">
    <v-text-field
      v-model="name"
      :counter="20"
      :label="$t('channel.field.name._')"
      :error-messages="errorOf('name')"
      required
    />

    <v-select
      v-model="visibility"
      :items="visibilities"
      :label="$t('channel.field.visibility._')"
      :error-messages="errorOf('visibility')"
      required
    />

    <v-text-field
      v-show="visibility === 'protected'"
      v-model="password"
      :label="$t('channel.field.password._')"
      :hint="editMode ? $t('channel.field.password.leave-empty') : null"
      :error-messages="errorOf('password')"
      required
    />

    <p v-if="error" class="red--text">
      {{ error }}
    </p>

    <v-btn :loading="loading" color="primary" class="mr-4" @click="submit()">
      {{ editMode ? 'edit' : 'create' }}
    </v-btn>
  </v-form>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import API from '~/api/API'
import JoiHelper from '~/utils/joi'

import { Channel, ChannelVisibility } from '~/models'

@Component
export default class Edit extends Vue {
  @Prop({ type: Object })
  initial!: Channel

  loading = false
  error: any = null
  validationErrors: { [key: string]: string } = {}

  name = ''
  visibility = ChannelVisibility.PUBLIC
  password = ''

  get visibilities() {
    return this.visibilityEnumValues.map((visibility) => ({
      text: this.$t(`channel.visibility.${visibility}`),
      value: visibility,
    }))
  }

  get visibilityEnumValues() {
    return [
      ChannelVisibility.PUBLIC,
      ChannelVisibility.PROTECTED,
      ChannelVisibility.PRIVATE,
    ]
  }

  errorOf(field: string) {
    const error = this.validationErrors[field]

    if (error === undefined) {
      return null
    }

    return [error]
  }

  get editMode() {
    return !!this.initial?.id
  }

  get actionUrl() {
    const id = this.initial?.id

    if (id) {
      return `/channels/${id}`
    }

    return `/channels`
  }

  async submit() {
    if (this.loading) {
      return
    }

    this.error = null
    this.validationErrors = {}

    try {
      const body = {
        name: this.name,
        visibility: this.visibility,
        password:
          this.visibility === ChannelVisibility.PROTECTED
            ? !this.password
              ? undefined
              : this.password
            : undefined,
      }

      let channel: Channel

      if (this.initial) {
        channel = await API.Channels.update(this.initial, body)
      } else {
        channel = await API.Channels.create(body)
      }

      this.$router.push(`/channels/${channel.id}`)
    } catch (error) {
      if (
        error.response?.status === 400 &&
        'validation' in error.response.data
      ) {
        this.error = 'validation error'
        JoiHelper.extract(error.response.data.validation, this.validationErrors)
      } else {
        this.error = error?.response?.data?.errors?.message || error
      }
    }

    this.loading = false
  }

  created() {
    if (this.initial) {
      this.name = this.initial.name
      this.visibility = this.initial.visibility
    }
  }
}
</script>
