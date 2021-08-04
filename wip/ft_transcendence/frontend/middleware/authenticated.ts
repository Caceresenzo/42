import { Middleware } from '@nuxt/types'
import { User } from '~/models'

const middleware: Middleware = ({ redirect, store }) => {
  if (!store.getters['auth/isAuthenticated']) {
    return redirect('/auth')
  }

  const user: User = store.state.auth.user
  if (user.doneFirstStep === false) {
    return redirect('/auth/first-step')
  }
}

export default middleware
