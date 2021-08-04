import Vue from 'vue'
import VueQrcode from '@chenfengyuan/vue-qrcode'
import { Plugin } from '@nuxt/types'

const plugin: Plugin = () => {
  Vue.component(VueQrcode.name, VueQrcode)
}

export default plugin
