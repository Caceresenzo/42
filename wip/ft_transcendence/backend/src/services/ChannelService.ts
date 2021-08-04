import { Container, Inject, Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import Achievement from "../entities/Achievement";
import Channel, { Type as ChannelType } from "../entities/Channel";
import ChannelUser from "../entities/ChannelUser";
import User from "../entities/User";
import Achievements from "../game/Achievements";
import ChannelRepository from "../repositories/ChannelRepository";
import AchievementProgressService from "./AchievementProgressService";
import ChannelUserService from "./ChannelUserService";
import SocketService from "./SocketService";

@Service()
export default class ChannelService {
  private get socketService() {
    return Container.get(SocketService);
  }

  constructor(
    @InjectRepository()
    private repository: ChannelRepository,

    @Inject()
    private channelUserService: ChannelUserService,

    @Inject()
    private achievementProgressService: AchievementProgressService
  ) {}

  public async allNotPrivate() {
    return await this.repository.findAllNotPrivate();
  }

  public async allNotDirect() {
    return await this.repository.findAllNotDirect();
  }

  public async findById(id: number) {
    return await this.repository.findOne(id);
  }

  public async findAllWhereUserIn(
    user: User,
    type = ChannelType.GROUP
  ): Promise<Channel[]> {
    const channelUsers =
      await this.channelUserService.findAllByUserAndNotBanned(user);

    return channelUsers.map((x) => x.channel).filter((x) => x.type === type);
  }

  public async create(channel: Channel) {
    channel.type = Channel.Type.GROUP;

    // TODO: Transactional?
    await this.repository.save(channel);
    await this.channelUserService.createOwner(channel);

    this.socketService.broadcastNewChannel(channel);

    await this.achievementProgressService.unlock(
      Achievements.COMMUNITY_CREATOR,
      channel.owner
    );

    return channel;
  }

  async createDirect(user1: User, user2: User) {
    const channel = new Channel();
    channel.type = Channel.Type.DIRECT;
    channel.visibility = Channel.Visibility.PRIVATE;

    await this.repository.save(channel);

    await this.channelUserService.create(channel, user1, false);
    if (!user1.is(user2)) {
      await this.channelUserService.create(channel, user2, false);
    }

    return channel;
  }

  public async update(channel: Channel) {
    await this.repository.save(channel);

    const users = (
      await this.channelUserService.findAllByChannelNotBanned(channel)
    ).map((x) => x.user);

    this.socketService.broadcastChannelUpdate(channel, users);
  }

  public async transferOwnership(channel: Channel, channelUser: ChannelUser) {
    channel.owner = channelUser.user;

    await this.channelUserService.setAdmin(channelUser, true);
    await this.repository.save(channel);

    this.socketService.broadcastChannelOwnerTransfer(channel);

    return channel;
  }

  async delete(channel: Channel) {
    await this.repository.delete(channel);

    this.socketService.broadcastChannelDelete(channel);
  }
}
