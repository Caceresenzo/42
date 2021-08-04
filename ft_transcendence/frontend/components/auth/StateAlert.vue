<template>
  <v-alert v-if="exists" :type="type"> {{ message }} </v-alert>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

interface State {
  message: string
  error: boolean
}

@Component
export default class ComponentImpl extends Vue {
  @Prop()
  state!: string

  states: { [key: string]: State } = {
    banned: {
      message: 'banned',
      error: true,
    },
    error: {
      message: 'failed to authenticate',
      error: true,
    },
    'unlock-error': {
      message: 'failed to unlock',
      error: true,
    },
    success: {
      message: 'success',
      error: false,
    },
    'unlock-success': {
      message: 'unlock success',
      error: false,
    },
  }

  get stateInfo(): State | null {
    return this.states[this.state]
  }

  get exists(): boolean {
    return !!this.stateInfo
  }

  get type() {
    return this.stateInfo!.error ? 'error' : 'info'
  }

  get message() {
    return this.stateInfo!.message
  }
}
</script>
