import { defineStore } from 'pinia'
import axios from "axios"
import { Tokens, User } from '~/models'

const ACCESS_TOKEN_KEY = "auth.accessToken"
const REFRESH_TOKEN_KEY = "auth.refreshToken"

export const useAuthStore = defineStore('auth', {
    state: () => ({
        initialized: false,
        tokens: null as Tokens | null,
        user: null as User | null
    }),
    getters: {
        logged(state) {
            return !!state.user
        }
    },
    actions: {
        async login(login: string, password: string) {
            const response = await axios.post(`/api/auth/login`, { login, password })

            const { accessToken, refreshToken }: Tokens = response.data
            this.updateTokens(accessToken, refreshToken)

            await this.fetchUser()
        },
        async logout() {
            await axios.post(`/api/auth/logout`, this.tokens)

            this.tokens = null
            this.user = null
        },
        async fetchUser() {
            try {
                const response = await axios.get(`/api/auth/self`, {
                    headers: {
                        Authorization: `Bearer ${this.tokens?.accessToken}`
                    }
                })

                this.user = response.data
                return this.user
            } catch (error) {
                this.user = null
                return null
            }
        },
        updateTokens(accessToken: string, refreshToken: string) {
            this.tokens = {
                accessToken,
                refreshToken
            }

            localStorage.setItem(ACCESS_TOKEN_KEY, accessToken || "")
            localStorage.setItem(REFRESH_TOKEN_KEY, refreshToken || "")
        },
        async initialize() {
            if (this.initialized) {
                return
            }
            this.initialized = true

            const accessToken = localStorage.getItem(ACCESS_TOKEN_KEY)
            const refreshToken = localStorage.getItem(REFRESH_TOKEN_KEY)

            if (accessToken && refreshToken) {
                this.updateTokens(accessToken, refreshToken)
                this.fetchUser().catch(console.log)
            }
        }
    },
})
