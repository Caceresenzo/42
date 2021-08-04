import { Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import User from "../entities/User";
import UserStatitics from "../entities/UserStatistics";
import UserStatiticsRepository from "../repositories/UserStatiticsRepository";

@Service()
export default class UserStatisticsService {
  constructor(
    @InjectRepository()
    private readonly repository: UserStatiticsRepository
  ) {}

  async getByUser(user: User): Promise<UserStatitics> {
    let statistics = await this.repository.findByUser(user);

    if (!statistics) {
      statistics = new UserStatitics();
      statistics.user = user;

      await this.repository.save(statistics);
    }

    return statistics;
  }

  async incrementWinCount(user: User, byValue = 1): Promise<UserStatitics> {
    return await this.increment(user, "winCount", byValue);
  }

  async incrementLossCount(user: User, byValue = 1): Promise<UserStatitics> {
    return await this.increment(user, "lossCount", byValue);
  }

  private async increment<K extends keyof UserStatitics>(
    user: User,
    field: K,
    byValue: number
  ): Promise<UserStatitics> {
    const statistics = (await this.getByUser(user)) as any;

    if (byValue) {
      statistics[field] += byValue;

      this.repository.save(statistics);
    }

    return statistics;
  }
}
