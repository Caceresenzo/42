import { Service } from "typedi";
import { EntityRepository, Repository } from "typeorm";
import Relationship, { Type } from "../entities/Relationship";
import User from "../entities/User";

@Service()
@EntityRepository(Relationship)
export default class RelationshipRepository extends Repository<Relationship> {
  async findByUserAndPeer(user: User, peer: User) {
    return this.findOne({ user, peer });
  }

  async findAllByUserAndType(user: User, type: Type) {
    return this.find({ user, type });
  }

  async findAllByUser(user: User) {
    return this.find({ user });
  }
}
