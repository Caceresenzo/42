import { User } from './User'

export enum Phase {
  TWO_FACTOR = '2fa',
}

export interface PhaseToken {
  phase: Phase
  user: User
  token: string
}
