import { Service } from "typedi";
import { Like, Repository } from "typeorm";
import { InjectRepository } from "typeorm-typedi-extensions";
import Channel from "../entities/Channel";
import User from "../entities/User";
import ChannelRepository from "../repositories/ChannelRepository";
import UserRepository from "../repositories/UserRepository";

declare type Class<T> = { new (): T; name: string };

interface Config {
  repository: Repository<any>;
  fields: Array<string>;
  key: string;
}

function nameOf(clazz: Class<any>) {
  return clazz.name.toLowerCase();
}

@Service()
export default class SearchService {
  private configs: {
    [key: string]: Config;
  };

  constructor(
    @InjectRepository() userRepository: UserRepository,
    @InjectRepository() channelRepository: ChannelRepository
  ) {
    this.configs = {
      [nameOf(User)]: {
        repository: userRepository,
        fields: ["username"],
        key: "users"
      },
      [nameOf(Channel)]: {
        repository: channelRepository,
        fields: ["name"],
        key: "channels"
      },
    };
  }

  public async search<T>(clazz: Class<T>, query: string): Promise<T[]> {
    const config = this.configs[nameOf(clazz)];

    return await this.doSearch(config, query);
  }

  public async searchAll(query: string) {
    const results = {};

    for (const config of Object.values(this.configs)) {
      results[config.key] = await this.doSearch(config, query);
    }

    return results;
  }

  private async doSearch(config: Config, query: string): Promise<any[]> {
    return await config.repository.find({
      where: config.fields.map((field) => ({ [field]: Like(`%${query}%`) })),
    });
  }
}
