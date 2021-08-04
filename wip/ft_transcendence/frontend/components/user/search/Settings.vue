<template>
  <v-menu bottom left offset-y :close-on-content-click="false">
    <template #activator="{ on, attrs }">
      <v-btn icon class="mr-2" v-bind="attrs" v-on="on">
        <v-icon>mdi-cog</v-icon>
      </v-btn>
    </template>

    <v-list>
      <v-list-item>
        <v-list-item-action>
          <v-switch v-model="hideBlockedModel" color="primary" />
        </v-list-item-action>
        <v-list-item-title>Hide blocked</v-list-item-title>
      </v-list-item>

      <v-list-item>
        <v-list-item-action>
          <v-switch v-model="hideBannedModel" color="primary" />
        </v-list-item-action>
        <v-list-item-title>Hide banned</v-list-item-title>
      </v-list-item>
    </v-list>
  </v-menu>
</template>

<script lang="ts">
import { Component, Prop, Vue } from 'nuxt-property-decorator'

@Component
export default class Settings extends Vue {
  @Prop()
  hideBlocked!: boolean

  @Prop()
  hideBanned!: boolean

  get hideBlockedModel() {
    return this.hideBlocked
  }

  set hideBlockedModel(val) {
    this.$emit('update:hideBlocked', val)
  }

  get hideBannedModel() {
    return this.hideBanned
  }

  set hideBannedModel(val) {
    this.$emit('update:hideBanned', val)
  }
}
</script>
