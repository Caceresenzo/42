<template>
  <v-dialog v-model="dialog" width="500" overly-opacity="3">
    <template #activator="{ on, attrs }">
      <v-btn
        class="ma-10"
        dark
        style="min-width: 200px"
        v-bind="attrs"
        v-on="on"
      >
        How to play
        <v-icon dark right> mdi-help-circle </v-icon>
      </v-btn>
    </template>

    <v-card>
      <v-card-title> Press up and down arrows to move your pad </v-card-title>

      <v-card-text>
        A small ball moves across the screen, bouncing off the top and bottom
        ledges, and the two players each control a pad, sliding it vertically
        between the ends of the screen using the controls. If the ball hits the
        pad, it bounces back to the other player. If it misses the pad, the
        other player scores a point. The ball bounces in different ways
        depending on how it hits the pad.
      </v-card-text>

      <v-divider />

      <v-card-actions>
        <v-spacer />

        <v-btn color="primary" text @click="dialog = false"> close </v-btn>
      </v-card-actions>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class HowToPlay extends Vue {
  dialog = false
}
</script>
