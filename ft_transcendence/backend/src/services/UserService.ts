import fileUpload = require("express-fileupload");
import { Service, Inject } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import User from "../entities/User";
import UserRepository from "../repositories/UserRepository";
import AvatarService from "./AvatarService";

@Service()
export default class UserService {
  constructor(
    @InjectRepository()
    private readonly repository: UserRepository,

    @Inject()
    private readonly avatarService: AvatarService
  ) {}

  async findById(id: number): Promise<User> {
    return this.repository.findOne(id);
  }

  async findByEmail(email: string): Promise<User> {
    return this.repository.findByEmail(email);
  }

  async findByUsername(username: string) {
    return this.repository.findByUsername(username);
  }

  async save(user: User): Promise<User> {
    return this.repository.save(user);
  }

  async all(): Promise<User[]> {
    return this.repository.find();
  }

  async hasNoUser(): Promise<boolean> {
    return (await this.repository.count()) === 0;
  }

  async fitUsername(input: string): Promise<string> {
    let suffix: string | number = "";
    let username: string;

    do {
      username = `${input}${suffix}`;

      if (typeof suffix === "number") {
        suffix++;
      } else {
        suffix = 1;
      }
    } while (await this.repository.existsByUsername(username));

    return username;
  }

  async firstStep(user: User, username: string): Promise<boolean> {
    const already = await this.findByUsername(username);

    if (already && already.id != user.id) {
      return false; /* already taken */
    }

    user.username = username;
    user.doneFirstStep = true;

    await this.save(user);

    return true;
  }

  async setBanned(user: User, newState: boolean): Promise<User> {
    if (user.banned != newState) {
      user.banned = newState;

      await this.save(user);
    }

    return user;
  }

  async updateAvatar(
    user: User,
    image: fileUpload.UploadedFile
  ): Promise<User> {
    const hash = await this.avatarService.store(image, user.picture);

    user.picture = hash;

    await this.save(user);

    return user;
  }
}
