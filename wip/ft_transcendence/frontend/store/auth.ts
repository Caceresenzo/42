import { Module, VuexModule, Action, Mutation } from 'vuex-module-decorators'
import { AuthProvider, User } from '~/models'
import { $axios } from '~/utils/api'
import { relationshipsStore } from '~/utils/store-accessor'

const DEFAULT_WIDTH = 470
const DEFAULT_HEIGHT = 580

interface Tokens {
  accessToken: string | null
  refreshToken: string | null
}

@Module({
  stateFactory: true,
  namespaced: true,
  name: 'auth',
})
class AuthModule extends VuexModule {
  providers: { [key: string]: AuthProvider } = {
    google: {
      name: 'Google',
      width: DEFAULT_WIDTH,
      height: DEFAULT_HEIGHT,
    },
    marvin: {
      name: '42',
      width: DEFAULT_WIDTH,
      height: DEFAULT_HEIGHT,
    },
  }

  accessToken: string | null = null

  refreshToken: string | null = null

  user: User | null = null

  @Mutation
  setTokens(tokens: Tokens): void {
    this.accessToken = tokens.accessToken
    this.refreshToken = tokens.refreshToken
  }

  @Mutation
  setUser(user: User | null): void {
    this.user = user
  }

  get isAuthenticated(): boolean {
    return !!this.user
  }

  get isAdmin(): boolean {
    return this.user?.admin === true
  }

  get picture(): string | null {
    if (!this.user) {
      return null
    }

    return `/api/users/${this.user.id}/avatar`
  }

  @Action
  restoreTokens() {
    const accessToken = localStorage.getItem('AUTH_ACCESS_TOKEN')
    const refreshToken = localStorage.getItem('AUTH_REFRESH_TOKEN')

    if (accessToken && refreshToken) {
      this.setTokens({
        accessToken,
        refreshToken,
      })
    }
  }

  @Action({ commit: 'setTokens', rawError: true })
  updateTokens(tokens: Tokens) {
    const { accessToken, refreshToken } = tokens

    if (accessToken && refreshToken) {
      localStorage.setItem('AUTH_ACCESS_TOKEN', accessToken)
      localStorage.setItem('AUTH_REFRESH_TOKEN', refreshToken)
    }

    return tokens
  }

  @Action({ commit: 'setTokens', rawError: true })
  clearTokens(): Tokens {
    localStorage.removeItem('AUTH_ACCESS_TOKEN')
    localStorage.removeItem('AUTH_REFRESH_TOKEN')

    return {
      accessToken: null,
      refreshToken: null,
    }
  }

  @Action({ rawError: true })
  async refreshTokens(): Promise<void> {
    const { accessToken, refreshToken } = await $axios.$post(
      '/auth/refresh-token',
      {
        accessToken: this.accessToken,
        refreshToken: this.refreshToken,
      }
    )

    this.updateTokens({
      accessToken,
      refreshToken,
    })
  }

  @Action({ rawError: true })
  logout(): void {
    this.clearTokens()
    this.setUser(null)
  }

  @Action({ commit: 'setUser', rawError: true })
  async fetch(): Promise<User> {
    const user: User = await $axios.$get('/users/@me')

    await relationshipsStore.fetchAll()

    return user
  }
}

export default AuthModule
