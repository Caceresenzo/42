<template>
  <v-list-item @click>
    <v-list-item-icon v-if="icon">
      <v-icon>{{ icon }}</v-icon>
    </v-list-item-icon>
    <v-list-item-title>{{ title }}</v-list-item-title>
  </v-list-item>
</template>

<script lang="ts">
import Vue, { PropType } from 'vue'

export default Vue.extend({
  props: {
    icon: {
      type: String as PropType<string>,
      required: false,
      default: null,
    },
    title: {
      type: String as PropType<string>,
      required: true,
    },
  },
})
</script>
