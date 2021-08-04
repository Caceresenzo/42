import { Service } from "typedi";
import { EntityRepository, LessThan, Not, Repository } from "typeorm";
import Channel from "../entities/Channel";
import ChannelUser from "../entities/ChannelUser";
import User from "../entities/User";

@Service()
@EntityRepository(ChannelUser)
export class ChannelUserRepository extends Repository<ChannelUser> {
  async findByChannelAndUser(channel: Channel, user: User) {
    return await this.findOne({ channel, user });
  }

  async findAllByChannelNotBanned(channel: Channel) {
    return await this.find({
      channel,
      banned: false,
    });
  }

  async findAllByUserAndNotBannedIncludeChannel(user: User) {
    return await this.find({
      where: {
        user,
        banned: false,
      },
      relations: ["channel"],
    });
  }

  async findAllByMutedTrueAndMutedUntilLessThan(date: Date) {
    return await this.find({
      where: {
        muted: true,
        mutedUntil: LessThan(date),
      },
    });
  }
}
