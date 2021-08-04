import { Service } from "typedi";
import { EntityRepository, Repository } from "typeorm";
import Channel from "../entities/Channel";
import DirectMessage from "../entities/DirectMessage";
import User from "../entities/User";

@Service()
@EntityRepository(DirectMessage)
export class DirectMessageRepository extends Repository<DirectMessage> {
  async findByUserAndPeer(user: User, peer: User) {
    return await this.findOne({ user, peer });
  }

  async findAllByUser(user: User): Promise<Array<DirectMessage>> {
    return await this.find({ user });
  }

  async findByChannel(channel: Channel): Promise<DirectMessage> {
    return await this.findOne({ channel });
  }
}
