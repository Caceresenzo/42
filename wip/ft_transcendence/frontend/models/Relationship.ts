import { User } from './User'

export enum RelationshipType {
  FRIEND = 'friend',
  BLOCK = 'block',
  INCOMING = 'incoming',
  OUTCOMING = 'outcoming',
}

export interface Relationship {
  type: RelationshipType
  peer: User
}
