import { $axios } from '../utils/api'
import { User } from '~/models'

export default class SearchAPI {
  static users(query: string): Promise<Array<User>> {
    if (!query || !query.length) {
      return Promise.resolve([])
    }

    return $axios.$get(`/search/users`, {
      params: {
        query,
      },
    })
  }
}
