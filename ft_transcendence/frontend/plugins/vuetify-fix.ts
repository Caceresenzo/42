import { Plugin } from '@nuxt/types'

const plugin: Plugin = ({ $vuetify }) => {
  $vuetify.application.register = function (
    uid: number,
    location: any,
    size: number
  ) {
    this.application[location][uid] = size
    this.update(location)
  }
}

export default plugin
