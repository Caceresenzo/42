import colors from 'vuetify/es5/util/colors'

export default {
  // Disable server-side rendering: https://go.nuxtjs.dev/ssr-mode
  ssr: false,

  router: {
    history: 'history',
  },

  // Global page headers: https://go.nuxtjs.dev/config-head
  head: {
    titleTemplate: '%s - ft-transcendence',
    title: 'ft-transcendence',
    htmlAttrs: {
      lang: 'en',
    },
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      { hid: 'description', name: 'description', content: '' },
    ],
    link: [{ rel: 'icon', type: 'image/x-icon', href: '/favicon.ico' }],
  },

  // Global CSS: https://go.nuxtjs.dev/config-css
  css: ['~/assets/double-drawer', '~/assets/scrollbar', '~/assets/fix'],

  // Plugins to run before rendering page: https://go.nuxtjs.dev/config-plugins
  plugins: [
    '~/plugins/vuetify-fix',
    '~/plugins/axios',
    '~/plugins/auth',
    {
      src: '~/plugins/socket',
      ssr: false,
    },
    '~/plugins/vuetify-confirm',
    '~/plugins/qrcode',
    '~/plugins/virtual-scroller',
    '~/plugins/virtual-scroll-list',
  ],

  // Auto import components: https://go.nuxtjs.dev/config-components
  components: true,

  // Modules for dev and build (recommended): https://go.nuxtjs.dev/config-modules
  buildModules: [
    // https://go.nuxtjs.dev/typescript
    '@nuxt/typescript-build',
    // https://go.nuxtjs.dev/vuetify
    '@nuxtjs/vuetify',

    '@nuxtjs/proxy',
  ],

  // Modules: https://go.nuxtjs.dev/config-modules
  modules: [
    // https://go.nuxtjs.dev/axios
    '@nuxtjs/axios',

    [
      'nuxt-i18n',
      {
        vuex: false,
        vueI18nLoader: true,
        defaultLocale: 'en',
        locales: [
          {
            code: 'en',
            name: 'English',
            file: 'en.js',
          },
        ],
        lazy: true,
        langDir: '~/locales/',
        vueI18n: {
          locale: 'en',
          fallbackLocale: 'en',
        },
      },
    ],

    'vuetify-dialog/nuxt',
  ],

  vuetifyDialog: {
    property: '$dialog',
  },

  proxy: {
    '/api': {
      changeOrigin: false,
      pathRewrite: { '^/api/': '/' },
      target: 'http://ft-transcendence-backend:3001/',
    },
  },

  // Axios module configuration: https://go.nuxtjs.dev/config-axios
  axios: {},

  // Vuetify module configuration: https://go.nuxtjs.dev/config-vuetify
  vuetify: {
    customVariables: ['~/assets/variables.scss'],
    theme: {
      dark: true,
      themes: {
        light: {
          primary: '#355DFF',
        },
        dark: {
          primary: '#355DFF',
          accent: colors.grey.darken3,
          secondary: colors.amber.darken3,
          info: colors.teal.lighten1,
          warning: colors.amber.base,
          error: colors.deepOrange.accent4,
          success: colors.green.accent3,
        },
      },
    },
  },

  // Build Configuration: https://go.nuxtjs.dev/config-build
  build: {
    babel: {
      plugins: [['@babel/plugin-proposal-private-methods', { loose: true }]],
    },
    extractCSS: {
      allChunks: true,
    },
  },
}
