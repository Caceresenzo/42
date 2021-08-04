import * as crypto from "crypto";
import { Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import config from "../config";
import PhaseToken, { Phase } from "../entities/PhaseToken";
import User from "../entities/User";
import PhaseTokenRepository from "../repositories/PhaseTokenRepository";

@Service()
export default class PhaseTokenService {
  constructor(
    @InjectRepository()
    private readonly repository: PhaseTokenRepository
  ) {}

  async create(user: User, phase: Phase) {
    const phaseToken = new PhaseToken();

    phaseToken.user = user;
    phaseToken.phase = phase;
    phaseToken.token = this.randomToken();

    await this.repository.save(phaseToken);

    return phaseToken;
  }

  async delete(phaseToken: PhaseToken) {
    await this.repository.save(phaseToken);
  }

  async findByTokenAndPhase(token: string, phase: Phase) {
    return await this.repository.findByTokenAndPhase(token, phase);
  }

  private randomToken() {
    return crypto.randomBytes(config.PHASE_TOKEN_LENGTH).toString("hex");
  }
}
