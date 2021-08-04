import { Service } from "typedi";
import { Repository, EntityRepository } from "typeorm";
import ChannelMessage from "../entities/ChannelMessage";

@Service()
@EntityRepository(ChannelMessage)
export default class ChannelMessageRepository extends Repository<ChannelMessage> {}
