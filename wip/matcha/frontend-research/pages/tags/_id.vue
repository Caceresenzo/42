<template>
  <div v-if="tag">
    <nuxt-child :key="tagId" :tag="tag" />
  </div>
</template>

<script lang="ts">
import {
  defineComponent,
  ref,
  useContext,
  useFetch,
  watch,
} from '@nuxtjs/composition-api'
import { usePathValue } from '~/composables'
import { Tag } from '~/models'
export default defineComponent({
  setup() {
    const { $axios } = useContext()

    const tag = ref<Tag>()
    const tagId = usePathValue('id')

    const { fetch } = useFetch(async () => {
      tag.value = await $axios.$get(`/api/tags/${tagId.value}`)
    })

    watch(tagId, fetch)

    return {
      tag,
      tagId,
    }
  },
})
</script>
