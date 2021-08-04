import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import User from "../entities/User";
import UserStatitics from "../entities/UserStatistics";

@Service()
@EntityRepository(UserStatitics)
export default class UserStatiticsRepository extends Repository<UserStatitics> {
  public findByUser(user: User) {
    return this.findOne({ user });
  }
}
