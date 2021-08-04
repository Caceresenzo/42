<template>
  <v-tooltip v-if="tooltip" left>
    <template #activator="{ attrs, on }">
      <v-icon color="primary" v-bind="attrs" v-on="on"> mdi-{{ icon }} </v-icon>
    </template>
    <span>{{ tooltip }}</span>
  </v-tooltip>
  <v-icon v-else color="primary"> mdi-{{ icon }} </v-icon>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Channel, ChannelVisibility } from '~/models'

@Component
export default class CompomentImpl extends Vue {
  @Prop()
  channel!: Channel

  get isProtected() {
    return this.channel.visibility === ChannelVisibility.PROTECTED
  }

  get isPrivate() {
    return this.channel.visibility === ChannelVisibility.PRIVATE
  }

  get icon() {
    if (this.isPrivate) {
      return 'cancel'
    }

    if (this.isProtected) {
      return 'lock'
    }

    return null
  }

  get tooltip() {
    if (this.isPrivate) {
      return 'private'
    }

    if (this.isProtected) {
      return 'protected by a password'
    }

    return null
  }
}
</script>
