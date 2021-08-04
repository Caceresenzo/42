export interface User {
  id: number
  username: string
  email?: string
  banned: boolean
  admin?: boolean
  picture?: string
  doneFirstStep?: boolean
}
