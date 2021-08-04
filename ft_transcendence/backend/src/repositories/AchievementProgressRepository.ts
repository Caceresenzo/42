import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import Achievement from "../entities/Achievement";
import AchievementProgress from "../entities/AchievementProgress";
import User from "../entities/User";

@Service()
@EntityRepository(AchievementProgress)
export default class AchievementProgressRepository extends Repository<AchievementProgress> {

  public async findAllByUser(user: User) {
    return await this.find({ user });
  }

  public async findByAchievementAndUser(achievement: Achievement, user: User) {
    return await this.findOne({ achievement, user });
  }

}
