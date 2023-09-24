<template>
  <v-card>
    <v-card-title>
      Picture
      <v-spacer />
      <div style="width: 200px">
        <v-file-input
          v-model="file"
          solo-inverted
          placeholder="New picture..."
          hide-details
          dense
        />
      </div>
    </v-card-title>
    <v-card-text>
      <v-row>
        <v-col v-for="picture in page.content" :key="picture.id">
          <v-card outlined>
            <v-card-text class="d-flex justify-center">
              <v-img
                min-height="200"
                max-height="200"
                min-width="200"
                max-width="200"
                :src="`/api/pictures/${picture.id}/view`"
              />
            </v-card-text>
            <v-card-actions>
              <v-btn
                color="primary"
                class="grow"
                :disabled="picture.default"
                @click="changeDefault(picture)"
              >
                set default
              </v-btn>
              <v-btn color="error" class="grow" @click="promptDelete(picture)">
                delete
              </v-btn>
            </v-card-actions>
          </v-card>
        </v-col>
      </v-row>
    </v-card-text>
    <v-card-actions>
      <v-spacer />
      <v-pagination
        :length="page.pagination.totalPages"
        :value="page.pagination.pageNumber + 1"
        @input="page.change($event - 1)"
        @next="page.next"
        @previous="page.previous"
      />
      <v-spacer />
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import {
  defineComponent,
  ref,
  useContext,
  watch,
} from '@nuxtjs/composition-api'
import { extractMessage, usePageable } from '~/composables'
import { Picture } from '~/models'
import { useAuthStore } from '~/store'
export default defineComponent({
  setup() {
    const { $dialog, $axios } = useContext()

    const page = usePageable<Picture>('/api/pictures', { watchAuth: true, clearOnRefresh: false })
    const file = ref<File>()

    const promptDelete = async (picture: Picture) => {
      const response = await $dialog.confirm({ title: 'Delete picture?' })
      if (!response) {
        return
      }

      try {
        await $axios.$delete(`/api/pictures/${picture.id}`)
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }

      page.fetch()
    }

    const changeDefault = async (picture: Picture) => {
      try {
        await $axios.$patch(`/api/pictures/${picture.id}`, {
          isDefault: true,
        })

        $dialog.notify.success('Changed default picture!')
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }
      
      page.fetch()
    }

    const upload = async () => {
      try {
        const formData = new FormData()
        formData.append('file', file.value!)

        await $axios.$post(`/api/pictures`, formData)
      } catch (error) {
        const message = extractMessage(error)
        $dialog.notify.error(message)
      }

      file.value = undefined
      page.fetch()
    }

    watch(file, (file) => {
      if (file) {
        upload()
      }
    })

    return {
      page,
      file,
      promptDelete,
      changeDefault,
    }
  },
})
</script>
