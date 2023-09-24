<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> Who liked {{ user.login }}? </v-card-title>
        </v-card>
      </v-col>
      <v-col v-for="like in page.content" :key="like.id">
        <v-card>
          <v-card-title>{{ like.user.login }}</v-card-title>
          <v-card-actions>
            <v-btn color="primary" class="grow" :to="`/users/${like.user.id}`">
              view
            </v-btn>
          </v-card-actions>
        </v-card>
      </v-col>
      <v-col cols="12">
        <v-pagination
          :length="page.pagination.totalPages"
          :value="page.pagination.pageNumber + 1"
          @input="page.change($event - 1)"
          @next="page.next"
          @previous="page.previous"
        />
      </v-col>
    </v-row>
  </v-container>
</template>

<script lang="ts">
import { defineComponent, PropType, toRefs } from '@nuxtjs/composition-api'
import { usePageable } from '~/composables'
import { User } from '~/models'
export default defineComponent({
  props: {
    user: {
      type: Object as PropType<User>,
      required: true,
    },
  },
  setup(props) {
    const { user } = toRefs(props)
    
    const page = usePageable(`/api/likes`, {
        params: {
            peerId: user.value.id
        }
    })

    return {
      user,
      page,
    }
  },
})
</script>
