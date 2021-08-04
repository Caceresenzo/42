<template>
  <v-progress-circular
    :style="outlineStyle"
    value="100"
    :width="stroke"
    :color="color"
  >
    <v-avatar :size="avatarSize">
      <v-img
        v-if="user"
        :key="pictureKey"
        :height="avatarSize"
        :width="avatarSize"
        :src="url"
      />
      <v-icon v-else small>mdi-account-question</v-icon>
    </v-avatar>
  </v-progress-circular>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { User } from '~/models'
import { socketStore } from '~/store'

@Component
export default class Avatar extends Vue {
  @Prop({ type: Object })
  user!: User

  @Prop({ type: Number, default: 60 })
  size!: number

  @Prop({ type: Boolean })
  withoutState!: boolean

  @Prop({ type: String })
  src?: string

  get picture() {
    return `/api/users/${this.user.id}/avatar?key=${this.pictureKey}`
  }

  get pictureKey() {
    return this.user?.picture || 'null'
  }

  get online(): boolean {
    return socketStore.connectedUserIds.includes(this.user.id)
  }

  get playing(): boolean {
    return socketStore.playingUserIds.includes(this.user.id)
  }

  get color(): string {
    let color: string
    color = this.online ? 'green' : 'red'
    color = this.playing ? 'yellow' : color
    return color
  }

  get outlineStyle() {
    const px = `${this.size}px`

    return {
      height: px,
      width: px,
    }
  }

  get stroke() {
    if (this.withoutState) {
      return 0
    }

    return 4
  }

  get avatarSize() {
    return this.size - this.stroke
  }

  get url() {
    if (this.src) {
      return this.src
    }

    return this.picture
  }
}
</script>
