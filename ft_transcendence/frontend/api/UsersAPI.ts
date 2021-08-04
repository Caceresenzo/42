import { $axios } from '../utils/api'
import { User } from '~/models'

export default class UsersAPI {
  static index(): Promise<Array<User>> {
    return $axios.$get(`/users`)
  }

  static show(id: string | number): Promise<User> {
    return $axios.$get(`/users/${id}`)
  }
}
