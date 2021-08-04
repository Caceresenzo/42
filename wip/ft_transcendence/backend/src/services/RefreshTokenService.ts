import * as crypto from "crypto";
import { Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import config from "../config";
import RefreshToken from "../entities/RefreshToken";
import User from "../entities/User";
import AuthError from "../errors/AuthError";
import { RefreshTokenRepository } from "../repositories/RefreshTokenRepository";

@Service()
export default class RefreshTokenService {
  constructor(
    @InjectRepository()
    private readonly repository: RefreshTokenRepository
  ) {}

  async find(token: string): Promise<RefreshToken> {
    const refreshToken = await this.repository.findOne({
      where: { token },
      relations: ["user"],
    });

    if (!refreshToken) {
      throw new AuthError("invalid token");
    }

    if (!refreshToken.active) {
      throw new AuthError("inactive token");
    }

    if (refreshToken.expired) {
      throw new AuthError("expired token");
    }

    return refreshToken;
  }

  async generate(user: User): Promise<RefreshToken> {
    const refreshToken = new RefreshToken();
    refreshToken.user = user;
    refreshToken.token = this.randomToken();
    refreshToken.expires = new Date(Date.now() + 7 * 24 * 60 * 60 * 1000);

    return await this.repository.save(refreshToken);
  }

  async revoke(token: string | RefreshToken): Promise<RefreshToken> {
    const refreshToken = await this.getByType(token);

    refreshToken.revoked = new Date(Date.now());

    return await this.repository.save(refreshToken);
  }

  async getByType(token: string | RefreshToken): Promise<RefreshToken> {
    if (token instanceof RefreshToken) {
      return token;
    }

    return await this.find(token);
  }

  private randomToken() {
    return crypto.randomBytes(config.REFRESH_TOKEN_LENGTH).toString("hex");
  }
}
