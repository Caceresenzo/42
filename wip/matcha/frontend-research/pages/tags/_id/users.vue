<template>
  <v-container>
    <v-row>
      <v-col cols="12">
        <v-card>
          <v-card-title> #{{ tag.name }} </v-card-title>
        </v-card>
      </v-col>
      <v-col v-for="user in page.content" :key="user.id">
        <v-card>
          <v-card-title>{{ user.login }}</v-card-title>
          <v-card-actions>
            <v-btn color="primary" class="grow" :to="`/users/${user.id}`">
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
import {
  defineComponent,
  PropType,
  toRefs,
} from '@nuxtjs/composition-api'
import { usePageable } from '~/composables'
import { Tag, User } from '~/models'
export default defineComponent({
  props: {
    tag: {
      type: Object as PropType<Tag>,
      required: true,
    },
  },
  setup(props) {
    const { tag } = toRefs(props)

    const page = usePageable<User>(`/api/tags/${tag.value.id}/users`)

    return {
      tag,
      page,
    }
  },
})
</script>
