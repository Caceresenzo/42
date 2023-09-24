<template>
  <v-app v-if="loaded" dark>
    <socket-disconnected />
    <v-navigation-drawer
      v-model="drawer"
      mini-variant
      expand-on-hover
      clipped
      fixed
      app
    >
      <v-list>
        <v-list-item
          v-for="(item, i) in items"
          :key="i"
          :to="item.to"
          router
        >
          <v-list-item-action>
            <v-icon>{{ item.icon }}</v-icon>
          </v-list-item-action>
          <v-list-item-content>
            <v-list-item-title>{{ item.title }}</v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>
    <v-app-bar clipped-left fixed app>
      <v-app-bar-nav-icon
        v-if="!drawer || mobile"
        @click.stop="drawer = !drawer"
      />
      <v-toolbar-title> matcha </v-toolbar-title>
      <v-spacer />
      <auth-menu v-if="logged" />
      <auth-buttons v-else />
    </v-app-bar>
    <v-main>
      <v-container>
        <Nuxt />
      </v-container>
    </v-main>
  </v-app>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  onBeforeMount,
  PropType,
  ref,
  toRefs,
  useContext,
} from '@nuxtjs/composition-api'
import { useAuthStore, useSocketStore } from '~/store'
export default defineComponent({
  setup() {
    const { $vuetify } = useContext()
    const authStore = useAuthStore()
    const socketStore = useSocketStore()

    const loaded = ref(false)

    onBeforeMount(async () => {
      await authStore.initialize()
      await socketStore.initialize()
      loaded.value = true
    })

    const drawer = ref(true)
    const logged = computed(() => authStore.logged)
    const mobile = computed(() => $vuetify.breakpoint.mobile)

    return {
      drawer,
      logged,
      mobile,
      loaded,
      items: [
        {
          icon: 'mdi-apps',
          title: 'Welcome',
          to: '/',
        },
        {
          icon: 'mdi-account',
          title: 'Users',
          to: '/users',
        },
      ],
    }
  },
})
</script>
