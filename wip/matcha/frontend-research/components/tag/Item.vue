<template>
  <v-chip :color="tag.color" :to="to" :close="editable" @click:close="close" class="mr-2">
    #{{ tag.name }}
  </v-chip>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  PropType,
  toRefs,
} from '@nuxtjs/composition-api'
import { Tag } from '~/models'
export default defineComponent({
  props: {
    tag: {
      type: Object as PropType<Tag>,
      required: true,
    },
    editable: Boolean,
  },
  emits: {
    close: (tag: Tag) => true,
  },
  setup(props, { emit }) {
    const { tag, editable } = toRefs(props)

    const to = computed(() => (!editable.value ? `/tags/${tag.value.id}/users` : undefined))

    const close = () => emit('close', tag.value)

    return {
      tag,
      editable,
      to,
      close,
    }
  },
})
</script>
