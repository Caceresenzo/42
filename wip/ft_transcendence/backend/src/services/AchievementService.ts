import * as jsonwebtoken from "jsonwebtoken";
import { Inject, Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import config from "../config";
import Achievement from "../entities/Achievement";
import AchievementRepository from "../repositories/AchievementRepository";

@Service()
export default class AchievementService {
  constructor(
    @InjectRepository()
    private repository: AchievementRepository
  ) {}

  async all(): Promise<Achievement[]> {
    return await this.repository.find();
  }

  async findById(id: number): Promise<Achievement> {
    return await this.repository.findOne(id);
  }

  async save(achievement: Achievement): Promise<Achievement> {
    await this.repository.save(achievement);

    return achievement;
  }
}
