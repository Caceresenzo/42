import { useFetch, useContext, useRoute, useRouter } from "@nuxtjs/composition-api";
import { computed, ref } from "vue";
import { reactive, watch } from "vue-demi";
import { Page } from "~/models";
import { defu } from 'defu'
import { useAuthStore } from "~/store";
import { useQueryValue } from "./route";

interface Options {
    watchAuth?: boolean,
    clearOnRefresh?: boolean,
    params?: {[key: string]: any}
}

export function usePageable<T>(endpoint: string, options: Options = {}) {
    options = defu(options, {
        watchAuth: false,
        clearOnRefresh: true,
        params: {}
    })

    const { $axios } = useContext()

    const response = ref<Page<T>>()

    const content = computed(() => response.value?.content ?? Array<T>())
    const pagination = computed(() => ({
        totalElements: response.value?.totalElements ?? 0,
        first: response.value?.first ?? true,
        last: response.value?.last ?? true,
        pageNumber: response.value?.pageNumber ?? 0,
        totalPages: response.value?.totalPages ?? 0,
        pageSize: response.value?.pageSize ?? 0,
    }))

    const page = useQueryValue("page", 0, parseInt)
    const size = useQueryValue("size", 20, parseInt)

    const { fetch, fetchState } = useFetch(async () => {
        if (options.clearOnRefresh && response.value) {
            response.value.content = []
        }

        response.value = (await $axios.$get(endpoint, {
            params: {
                ...options.params,
                page: page.value,
                size: size.value,
            }
        }))
    })

    watch(page, fetch)

    if (options.watchAuth) {
        const authStore = useAuthStore()
        watch(() => authStore.logged, fetch)
    }

    const next = () => page.value++
    const previous = () => page.value--
    const change = (value: number) => page.value = value

    return reactive({
        content,
        pagination,
        fetch,
        fetchState,
        next,
        previous,
        change
    })
}