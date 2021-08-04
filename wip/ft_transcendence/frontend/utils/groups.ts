import { ChannelUser, Channel } from '../models'

interface UserGroup {
  name: string
  users: Array<ChannelUser>

  push(user: ChannelUser): void
}

export function groupByTypes(
  $t: (key: string) => string,
  users: Array<ChannelUser>,
  channel: Channel
): { [key: string]: UserGroup } {
  const makeGroup = (name: string) =>
    ({
      name: $t(`channel.group.${name}`),
      users: [],
      push(user) {
        this.users.push(user)
      },
    } as UserGroup)

  const owners = makeGroup('owner')
  const admins = makeGroup('admin')
  const normal = makeGroup('user')
  const banned = makeGroup('banned')

  for (const user of users) {
    if (user.id === channel.owner.id) {
      owners.push(user)
    } else if (user.banned) {
      banned.push(user)
    } else if (user.admin) {
      admins.push(user)
    } else {
      normal.push(user)
    }
  }

  return {
    owners,
    admins,
    users: normal,
    banned,
  }
}
