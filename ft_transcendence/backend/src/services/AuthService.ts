import * as jsonwebtoken from "jsonwebtoken";
import { Inject, Service } from "typedi";
import config from "../config";
import User from "../entities/User";
import AuthError from "../errors/AuthError";
import Tokens from "../models/Tokens";
import RefreshTokenService from "./RefreshTokenService";

@Service()
export default class AuthService {
  constructor(
    @Inject()
    private refreshTokenService: RefreshTokenService
  ) {}

  async refresh(token: string): Promise<Tokens> {
    const refreshToken = await this.refreshTokenService.revoke(token);
    const { user } = refreshToken;

    if (user.banned) {
      throw new AuthError("user banned");
    }

    const newRefreshToken = await this.refreshTokenService.generate(user);

    return {
      accessToken: this.signJwt(user),
      refreshToken: newRefreshToken.token,
    };
  }

  async authenticate(user: User): Promise<Tokens> {
    const refreshToken = await this.refreshTokenService.generate(user);

    return {
      accessToken: this.signJwt(user),
      refreshToken: refreshToken.token,
    };
  }

  private signJwt(user: User): string {
    const { id } = user;

    return jsonwebtoken.sign(
      {
        sub: id,
        id,
      },
      config.JWT_SECRET,
      {
        expiresIn: config.JWT_EXPIRATION,
      }
    );
  }
}
