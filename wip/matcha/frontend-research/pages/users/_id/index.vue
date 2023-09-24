<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title>
            {{ user.login }}
            <v-spacer />
            <v-btn color="primary" small :to="`/users/@me/edit`"> edit </v-btn>
          </v-card-title>
          <v-card-text>
            <pre><code class="d-block">{{ user }}</code></pre>
          </v-card-text>
          <v-card-text>
            <tag-item v-for="tag in tags" :key="tag.id" :tag="tag" />
          </v-card-text>
          <v-card-actions>
            <like-button :peer="user" />
            <block-button :peer="user" />
            <report-button :user="user" />
            <v-btn color="primary" :to="`/users/${user.id}/likes`">
              who liked?
            </v-btn>
            <v-btn color="primary" :to="`/users/${user.id}/messages`">
              messages
            </v-btn>
            <v-btn color="primary" :to="`/users/${user.id}/visits`">
              visits
            </v-btn>
          </v-card-actions>
        </v-card>
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import {
  defineComponent,
  onMounted,
  PropType,
  ref,
  toRefs,
  useContext,
  useFetch,
} from '@nuxtjs/composition-api'
import { Tag, User } from '~/models'
import { useAuthStore } from '~/store'
export default defineComponent({
  props: {
    user: {
      type: Object as PropType<User>,
      required: true,
    },
  },
  setup(props) {
    const { user } = toRefs(props)
    const { $axios } = useContext()

    const tags = ref(Array<Tag>())
    useFetch(async () => {
      tags.value = (
        await $axios.$get(`/api/users/${user.value.id}/tags`)
      ).content
    })

    onMounted(() => {
      $axios.post(`/api/users/${user.value.id}/visits`).catch(() => void 0)
    })

    return {
      user,
      tags,
    }
  },
})
</script>
