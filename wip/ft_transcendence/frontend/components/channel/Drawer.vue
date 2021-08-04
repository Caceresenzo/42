<template>
  <drawer-left>
    <template #prepend>
      <v-row class="ma-2">
        <v-col cols="10">
          <slot name="search">
            <v-text-field
              v-model="query"
              background-color="grey lighten-1"
              dense
              flat
              hide-details
              solo
              clearable
            />
          </slot>
        </v-col>
        <v-col cols="2" class="pl-0">
          <v-btn icon :loading="loading" @click="refresh">
            <v-icon>mdi-refresh</v-icon>
          </v-btn>
        </v-col>
      </v-row>

      <v-divider />

      <template v-if="$scopedSlots['before']">
        <slot name="before" />
        <v-divider />
      </template>
    </template>

    <v-alert v-if="error" type="error" class="ma-2">
      {{ error.message || 'error when fetching' }}
    </v-alert>

    <slot :items="filteredItems" />

    <template #append>
      <slot name="append" />
    </template>
  </drawer-left>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'
import { Socket } from 'vue-socket.io-extended'

@Component
export default class Drawer extends Vue {
  @Prop({ type: Boolean, default: false })
  loading!: boolean

  @Prop({ type: Object })
  error!: any

  @Prop({ type: Array })
  items!: Array<any>

  @Prop({ type: Function })
  filterer!: (query: string, item: any) => boolean

  query = ''

  get filteredItems() {
    return this.items.filter((item) => this.filterer(this.query, item))
  }

  refresh(): void {
    this.$emit('refresh')
  }

  @Socket('channel_new')
  onNewChannel() {
    this.refresh()
  }

  @Socket('channel_delete')
  onDeleteChannel() {
    this.refresh()
  }
}
</script>
