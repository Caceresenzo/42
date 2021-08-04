<template>
  <v-btn icon @click="$emit('click')">
    <v-icon>mdi-close</v-icon>
  </v-btn>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class ComponentImpl extends Vue {}
</script>
