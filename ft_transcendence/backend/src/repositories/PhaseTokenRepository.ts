import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import PhaseToken, { Phase } from "../entities/PhaseToken";

@Service()
@EntityRepository(PhaseToken)
export default class PhaseTokenRepository extends Repository<PhaseToken> {

  async findByTokenAndPhase(token: string, phase: Phase) {
    return await this.findOne({ token, phase })
  }

}
