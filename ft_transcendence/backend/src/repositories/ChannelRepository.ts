import { Service } from "typedi";
import { Repository, EntityRepository, Not } from "typeorm";
import Channel from "../entities/Channel";

@Service()
@EntityRepository(Channel)
export default class ChannelRepository extends Repository<Channel> {
  async findAllNotPrivate(): Promise<Array<Channel>> {
    return await this.find({ visibility: Not(Channel.Visibility.PRIVATE) });
  }

  async findAllNotDirect(): Promise<Array<Channel>> {
    return await this.find({ type: Not(Channel.Type.DIRECT) });
  }
}
