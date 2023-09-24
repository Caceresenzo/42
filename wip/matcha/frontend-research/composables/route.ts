import { useRoute, useRouter } from "@nuxtjs/composition-api";
import { computed } from "vue"

export function useQueryValue<T>(name: string, defaultValue?: T, parse?: (input: string) => T) {
    const route = useRoute()
    const router = useRouter()

    return computed<T>({
        get(): T {
            const value = route.value.query[name] as string || String(defaultValue)

            if (parse) {
                return parse(value)
            }

            return value as T
        },
        set(value: T) {
            router.push({
                query: {
                    ...route.value.query,
                    [name]: String(value)
                }
            })
        }
    })
}

export function usePathValue<T>(name: string, parse?: (input: string) => T) {
    const route = useRoute()

    return computed<T>(() => {
        const value = route.value.params[name] as string

        if (parse) {
            return parse(value)
        }

        return value as T
    })
}