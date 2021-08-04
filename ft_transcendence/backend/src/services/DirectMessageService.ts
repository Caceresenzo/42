import { Inject, Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import Channel from "../entities/Channel";
import DirectMessage from "../entities/DirectMessage";
import User from "../entities/User";
import { DirectMessageRepository } from "../repositories/DirectMessageRepository";
import ChannelService from "./ChannelService";

@Service()
export default class DirectMessageService {
  constructor(
    @InjectRepository()
    private readonly repository: DirectMessageRepository,

    @Inject()
    private readonly channelService: ChannelService
  ) {}

  async findByChannel(channel: Channel): Promise<DirectMessage> {
    return await this.repository.findByChannel(channel)
  }

  async findAllByUser(user: User): Promise<Array<DirectMessage>> {
    return await this.repository.findAllByUser(user)
  }

  async getOrCreate(user: User, peer: User) {
    let directMessage = await this.repository.findByUserAndPeer(user, peer);

    if (!directMessage) {
      const channel = await this.channelService.createDirect(user, peer);

      directMessage = await this.createRelation(user, peer, channel);

      if (!user.is(peer)) {
        this.createRelation(peer, user, channel);
      }
    }

    return directMessage;
  }

  private async createRelation(user: User, peer: User, channel: Channel) {
    const directMessage = new DirectMessage();
    directMessage.user = user;
    directMessage.peer = peer;
    directMessage.channel = channel;

    await this.repository.save(directMessage);

    return directMessage;
  }
}
