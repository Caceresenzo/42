<template>
  <v-list-item link :to="to">
    <v-list-item-content>
      <v-list-item-title>{{ channel.name }}</v-list-item-title>
      <v-list-item-subtitle>{{ channel.visibility }}</v-list-item-subtitle>
    </v-list-item-content>
  </v-list-item>
</template>

<script lang="ts">
import Vue, { PropType } from 'vue'

import { Channel } from '~/models'

export default Vue.extend({
  props: {
    channel: {
      type: Object as PropType<Channel>,
      required: true,
    },
  },
  computed: {
    to(): string {
      return `/channels/${this.channel.id}`
    },
  },
})
</script>
