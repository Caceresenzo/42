<template>
  <v-main class="fill-height" style="overflow: auto">
    <v-row class="ma-2" justify="center" align="center">
      <v-col justify="center" align="center">
        <p class="text-center ma-10" style="font-size: 40px">
          ft_transcendence
        </p>
        <v-img
          max-height="600"
          max-width="1000"
          :src="require('@/assets/intro.gif')"
          class="mt-12 mb-6"
        />
        <div class="text-center">
          <div>
            <home-button-how-to-play />
            <home-button-friend />
            <home-button-channel />
          </div>

          <div>
            <home-button-quick-play />
          </div>
        </div>
      </v-col>
    </v-row>
  </v-main>
</template>

<script lang="ts">
import { Component, Vue } from 'nuxt-property-decorator'

@Component
export default class Page extends Vue {
  head() {
    return {
      title: 'Home',
    }
  }
}
</script>
