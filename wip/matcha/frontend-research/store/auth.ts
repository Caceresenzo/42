import { defineStore } from 'pinia'
import axios from "axios"
import { User } from '~/models'

export const useAuthStore = defineStore('auth', {
    state: () => ({
        initialized: false,
        user: null as User | null
    }),
    getters: {
        logged(state) {
            return !!state.user
        }
    },
    actions: {
        async login(login: string, password: string) {
            await axios.post(`/api/auth/login`, { login, password })
            await this.fetchUser()
        },
        async logout() {
            await axios.post(`/api/auth/logout`, {})
            this.user = null
        },
        async fetchUser() {
            try {
                this.user = (await axios.get(`/api/auth/self`)).data
                return this.user
            } catch (error) {
                this.user = null
                return null
            }
        },
        async initialize() {
            if (this.initialized) {
                return
            }
            this.initialized = true

            await this.fetchUser().catch(console.log)

            const heartbeat = () => {
                if (this.logged) {
                    axios.get(`/api/heartbeat/log`).catch(() => void 0)
                }
            }

            setInterval(heartbeat, 2 * 60_000)
            heartbeat();
        }
    },
})
