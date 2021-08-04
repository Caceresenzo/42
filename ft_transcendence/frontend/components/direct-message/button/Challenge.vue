<template>
  <v-dialog v-model="dialog" max-width="600px">
    <template #activator="{ on, attrs }">
      <v-btn v-if="small" icon color="primary" v-bind="attrs" v-on="on">
        <v-icon>mdi-sword-cross</v-icon>
      </v-btn>
      <v-btn v-else color="primary" :block="block" v-bind="attrs" v-on="on">
        challenge
        <v-icon right>mdi-sword-cross</v-icon>
      </v-btn>
    </template>
    <v-card>
      <v-card-title>
        <v-icon left>mdi-cog</v-icon>
        Game options
      </v-card-title>
      <v-card-text>
        <v-container>
          <v-row>
            <v-col cols="12" sm="6">
              <v-select
                v-model="inputs.map"
                :loading="maps.length === 0"
                :items="maps"
                item-value="id"
                item-text="name"
                label="Map"
                required
              />
            </v-col>
            <v-col cols="12" sm="6">
              <v-select
                v-model="inputs.pointToWin"
                :items="[3, 5, 7, 9, 12]"
                label="Point to win"
                required
              />
            </v-col>
            <v-col cols="12" sm="6">
              <v-select
                v-model="inputs.ballVelocity"
                :items="[
                  {
                    text: 'Slow',
                    value: 1,
                  },
                  {
                    text: 'Normal',
                    value: 1.5,
                  },
                  {
                    text: 'Fast',
                    value: 3,
                  },
                  {
                    text: 'Very fast',
                    value: 5,
                  },
                ]"
                label="Ball speed"
                required
              ></v-select>
            </v-col>
            <v-col cols="12" sm="6">
              <v-select
                v-model="inputs.paddleVelocity"
                :items="[
                  {
                    text: 'Slow',
                    value: 1,
                  },
                  {
                    text: 'Normal',
                    value: 2,
                  },
                  {
                    text: 'Fast',
                    value: 3,
                  },
                  {
                    text: 'Very fast',
                    value: 4,
                  },
                ]"
                label="Paddle speed"
                required
              ></v-select>
            </v-col>
          </v-row>
        </v-container>
      </v-card-text>
      <v-card-actions>
        <v-spacer />
        <v-btn color="blue darken-1" text @click="dialog = false">Cancel</v-btn>
        <v-btn color="blue darken-1" text @click="submit">OK</v-btn>
      </v-card-actions>
    </v-card>
  </v-dialog>
</template>

<script lang="ts">
import { Component, Prop, Vue, Watch } from 'nuxt-property-decorator'
import { User } from '~/models'
import { Map } from '~/models/Game'

@Component
export default class Viewer extends Vue {
  @Prop({ type: Object, required: true })
  peer!: User

  @Prop({ type: Boolean })
  block!: boolean

  @Prop({ type: Boolean })
  neverSmall!: boolean

  loading = false
  dialog = false

  inputs = {
    map: 1,
    ballVelocity: 1.5,
    paddleVelocity: 2,
    pointToWin: 3,
  }

  maps: Array<Map> = []

  get small() {
    if (this.neverSmall) {
      return false
    }

    return this.$vuetify.breakpoint.name === 'xs'
  }

  async submit() {
    this.dialog = false
    if (this.loading) {
      return
    }

    this.loading = true

    try {
      await this.$axios.post(`pending-games`, {
        peerId: this.peer.id,
        ...this.inputs,
      })

      this.$emit('success')
    } catch (error) {
      this.$dialog.notify.error(`Could not challenge: ${error}`)
    }

    this.loading = false
  }

  async fetchMaps() {
    try {
      this.maps = await this.$axios.$get(`/maps`)
    } catch (error) {
      this.$dialog.notify.error(`Could not fetch maps: ${error}`)
    }
  }

  @Watch('dialog')
  onDialogOpen(val: boolean) {
    if (val && !this.maps.length) {
      this.fetchMaps()
    }
  }
}
</script>
