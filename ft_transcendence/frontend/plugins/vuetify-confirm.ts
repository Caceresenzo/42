import Vue from 'vue'
import VuetifyConfirm from 'vuetify-confirm'
import { Plugin } from '@nuxt/types'

const plugin: Plugin = ({ app }) => {
  Vue.use(VuetifyConfirm, { vuetify: app.vuetify })
}

export default plugin
