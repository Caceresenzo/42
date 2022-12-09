import Vuetify from "vuetify"

type $Vuetify = Vuetify["framework"]

declare module '@nuxt/vue-app' {
    interface Context {
        $vuetify: $Vuetify
    }
    interface NuxtAppOptions {
        $vuetify: $Vuetify
    }
}

// Nuxt 2.9+
declare module '@nuxt/types' {
    interface Context {
        $vuetify: $Vuetify
    }

    interface NuxtAppOptions {
        $vuetify: $Vuetify
    }

    interface Configuration {
        $vuetify: $Vuetify
    }
}

declare module 'vue/types/vue' {
    interface Vue {
        $vuetify: $Vuetify
    }
}