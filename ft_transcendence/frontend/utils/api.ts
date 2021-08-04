import { NuxtAxiosInstance } from '@nuxtjs/axios'
import { Socket } from 'socket.io-client'

// eslint-disable-next-line import/no-mutable-exports
let $axios: NuxtAxiosInstance

// eslint-disable-next-line import/no-mutable-exports
let $socket: Socket

export function initializeAxios(axiosInstance: NuxtAxiosInstance) {
  $axios = axiosInstance
}

export function initializeSocket(socketInstance: Socket) {
  $socket = socketInstance
}

export { $axios, $socket }
