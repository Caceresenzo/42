import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import User from "../entities/User";

@Service()
@EntityRepository(User)
export default class UserRepository extends Repository<User> {
  async findByUsername(username: string): Promise<User> {
    return await this.findOne({ username });
  }

  async findByEmail(email: string): Promise<User> {
    return await this.findOne({ email });
  }

  async existsByUsername(username: string): Promise<boolean> {
    return (await this.count({ username })) !== 0;
  }
}
