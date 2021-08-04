import { $axios } from '../utils/api'
import { Achievement } from '~/models'

export default class AchievementsAPI {
  static index(): Promise<Array<Achievement>> {
    return $axios.$get(`achievements`)
  }

  static show(achievement: Achievement): Promise<Achievement> {
    return $axios.$get(`achievements/${achievement.id}`)
  }
}
