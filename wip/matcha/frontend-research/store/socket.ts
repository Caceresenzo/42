import { defineStore } from 'pinia'
import { watch } from 'vue-demi'
import { useAuthStore } from './auth'

interface Packet {
    event: string
    payload: any
}

type PacketListener = (payload: any, event: string) => void 

export const useSocketStore = defineStore('socket', {
    state: () => ({
        initialized: false,
        socket: null as WebSocket | null,
        connected: false,
        listeners: {} as { [key: string]: Set<PacketListener> }
    }),
    actions: {
        addListener(event: string, listener: PacketListener) {
            if (!this.listeners[event]) {
                this.listeners[event] = new Set()
            }

            return this.listeners[event].add(listener)
        },
        removeListener(event: string, listener: PacketListener) {
            const set = this.listeners[event]

            if (set) {
                return set.delete(listener)
            }

            return false
        },
        connect() {
            const authStore = useAuthStore()
            const user = authStore.user

            if (!user) {
                return false
            }

            const schema = window.location.protocol == "https:" ? 'wss' : 'ws'
            // const url = `${schema}://localhost:4567/websocket`
            const url = `${schema}://${window.location.host}/api/websocket`

            const socket = new WebSocket(url)

            socket.onopen = () => {
                this.connected = true
            }

            socket.onclose = (event) => {
                if (!event.wasClean) {
                    this.connect()
                }

                console.log(event)
                
                this.connected = false
            }
            socket.onerror = console.log
            socket.onmessage = (event) => this.dispatch(JSON.parse(event.data))

            this.disconnect()
            this.socket = socket
        },
        disconnect() {
            this.socket?.close()
        },
        dispatch(packet: Packet) {
            console.log(packet)

            const { event, payload } = packet
            for (const listener of this.listeners[event] || []) {
                listener(payload, event)
            }
        },
        emit(event: string, payload: any) {
            const message = JSON.stringify({
                event,
                payload,
            })

            this.socket?.send(message)
        },
        initialize() {
            if (this.initialized) {
                return
            }
            this.initialized = true

            const authStore = useAuthStore()
            authStore.$subscribe(() => {
                if (authStore.logged) {
                    this.connect()
                } else {
                    this.disconnect()
                }
            }, { detached: true, immediate: true })
        }
    },
})
