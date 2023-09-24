<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Notifications </v-card-title>
          <v-list>
            <v-list-item
              v-for="notification in notifications"
              :key="notification.id"
              :to="notification.link"
            >
              <v-list-item-content>
                <v-list-item-title>
                  {{ notification.content }}
                </v-list-item-title>
              </v-list-item-content>
            </v-list-item>
          </v-list>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  defineComponent,
  onMounted,
  onUnmounted,
  ref,
} from '@nuxtjs/composition-api'
import { Notification } from '~/models'
import { useSocketStore } from '~/store'

const NOTIFICATION_CREATED_EVENT = 'notification.created'

export default defineComponent({
  setup() {
    const socketStore = useSocketStore()

    const notifications = ref(Array<Notification>())

    const onPacket = (payload: Notification) => {
      notifications.value.push(payload)
    }

    onMounted(() =>
      socketStore.addListener(NOTIFICATION_CREATED_EVENT, onPacket)
    )
    onUnmounted(() =>
      socketStore.removeListener(NOTIFICATION_CREATED_EVENT, onPacket)
    )

    return {
      notifications,
    }
  },
})
</script>
