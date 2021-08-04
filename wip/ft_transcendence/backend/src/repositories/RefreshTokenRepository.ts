import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import RefreshToken from "../entities/RefreshToken";

@Service()
@EntityRepository(RefreshToken)
export class RefreshTokenRepository extends Repository<RefreshToken> {
  public findByToken(token: string) {
    return this.findOne({ token });
  }
}
