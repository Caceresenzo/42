<template>
  <v-card>
    <v-card-title>
      Tags
      <v-spacer />
      <div style="width: 200px">
        <v-combobox
          ref="combo"
          :search-input.sync="name"
          :items="items"
          label="Add tag"
          placeholder="pizza"
          outlined
          dense
          item-text="name"
          item-value="name"
          hide-details
          @keydown.enter="add"
        />
      </div>
    </v-card-title>
    <v-card-text>
      <tag-item
        v-for="tag in tags"
        :key="tag.id"
        :tag="tag"
        editable
        @close="remove"
      />
    </v-card-text>
  </v-card>
</template>

<script lang="ts">
import {
  defineComponent,
  ref,
  useContext,
  useFetch,
  watch,
} from '@nuxtjs/composition-api'
import { extractMessage } from '~/composables'
import { Tag } from '~/models'
import { useAuthStore } from '~/store'
import { extractValidation } from '~/utils'
import debounce from 'lodash.debounce'
export default defineComponent({
  setup() {
    const { $dialog, $axios } = useContext()

    const authStore = useAuthStore()
    const loading = ref(false)

    const combo = ref<HTMLElement>()

    const user = authStore.user

    const tags = ref(Array<Tag>())
    useFetch(async () => {
      tags.value = (await $axios.$get(`/api/users/${user?.id}/tags`)).content
    })

    const name = ref('')
    const items = ref(Array<Tag>())

    watch(
      name,
      debounce(async () => {
        try {
          items.value = (
            await $axios.$get(`/api/tags`, {
              params: {
                query: name.value || '',
              },
            })
          ).content
        } catch (error) {
          const message = extractMessage(error)
          $dialog.notify.error(message)
        }
      })
    )

    const add = async () => {
      if (!name.value) {
        return
      }

      try {
        const tag = await $axios.$post(`/api/tags`, { name: name.value })
        await $axios.$post(`/api/users/${user?.id}/tags/${tag.id}`)

        tags.value.push(tag)
        $dialog.notify.success('Tag added!')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }

      name.value = ''
      combo.value!.blur()
    }

    const remove = async (tag: Tag) => {
      try {
        await $axios.$delete(`/api/users/${user?.id}/tags/${tag.id}`)

        tags.value.splice(
          tags.value.findIndex((item) => item.id === tag.id),
          1
        )
        $dialog.notify.success('Tag added!')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }
    }

    return {
      user,
      tags,
      loading,
      name,
      items,
      add,
      remove,
      combo,
    }
  },
})
</script>
