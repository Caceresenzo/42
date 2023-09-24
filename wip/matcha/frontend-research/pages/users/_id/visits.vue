<template>
  <v-row>
    <v-col>
      <v-card>
        <v-card-title> Visits </v-card-title>
        <v-list dense>
          <v-list-item v-for="visit in visits" :key="visit.id">
            <v-list-item-avatar>
              <v-avatar>
                <v-icon>mdi-account</v-icon>
              </v-avatar>
            </v-list-item-avatar>
            <v-list-item-content>
              <v-list-item-title>
                {{ getTitle(visit) }}
              </v-list-item-title>
              <v-list-item-subtitle>
                Visited your profile {{ visit.times }} times the {{ visit.date }} (between {{ visit.firstAt }} and {{ visit.lastAt }})
              </v-list-item-subtitle>
            </v-list-item-content>
          </v-list-item>
        </v-list>
      </v-card>
    </v-col>
  </v-row>
</template>

<script lang="ts">
import {
  defineComponent,
  PropType,
  ref,
  toRefs,
  useContext,
  useFetch,
} from '@nuxtjs/composition-api'
import { User, Visit } from '~/models'

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

    const visits = ref(Array<Visit>())

    const getTitle = (visit: Visit) => {
      return visit.user?.login || 'anonymous'
    }

    useFetch(async () => {
      visits.value = (await $axios.$get(`/api/users/${user.value.id}/visits`)).content
    })

    return {
      visits,
      getTitle,
    }
  },
})
</script>
