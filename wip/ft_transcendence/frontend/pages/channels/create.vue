<template>
  <div class="pa-4 fill-height" style="overflow-y: scroll">
    <v-app-bar app clipped-right>
      <v-toolbar-title>
        <drawer-menu />
        {{ $t('channel.create._') }}
      </v-toolbar-title>
    </v-app-bar>

    <v-row>
      <v-col cols="12">
        <channel-settings-card-edit />
      </v-col>
    </v-row>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Index extends Vue {}
</script>
