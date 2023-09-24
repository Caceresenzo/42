export function extractMessage(error: Error | any, defaultError?: string): string {
    if (!error) {
        return defaultError || ""
    }

    return error?.response?.data?.title || error?.message || String(error) || defaultError || 'An error occured'
}