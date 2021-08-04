<template>
  <page-centered-icon
    plain
    icon-class="animated-hand-icon"
    :text="text"
    icon="mdi-hand-pointing-left"
  />
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class NothingSelected extends Vue {
  @Prop({ type: String })
  text!: string
}
</script>

<style>
  .animated-hand-icon {
    position: relative;
    animation: bouncing-hand 1s infinite;
    animation-direction: alternate;
  }

  @keyframes bouncing-hand {
    0% {
      left: -20px;
    }
    100% {
      left: 20px;
    }
  }
</style>
