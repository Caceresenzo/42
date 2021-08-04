import { Inject, Service } from "typedi";
import { InjectRepository } from "typeorm-typedi-extensions";
import Relationship, {
  Type as RelationshipType
} from "../entities/Relationship";
import User from "../entities/User";
import Achievements from "../game/Achievements";
import RelationshipRepository from "../repositories/RelationshipRepository";
import AchievementProgressService from "./AchievementProgressService";
import SocketService from "./SocketService";

@Service()
export default class RelationshipService {
  constructor(
    @InjectRepository()
    private readonly repository: RelationshipRepository,

    @Inject()
    private readonly achievementProgressService: AchievementProgressService,

    @Inject()
    private readonly socketService: SocketService
  ) {}

  async all(user: User) {
    return this.repository.findAllByUser(user);
  }

  async findAllFriends(user: User) {
    return this.repository.findAllByUserAndType(user, RelationshipType.FRIEND);
  }

  async findRelationship(user: User, peer: User) {
    return await this.repository.findByUserAndPeer(user, peer);
  }

  async findRelationships(
    user: User,
    peer: User
  ): Promise<[Relationship, Relationship]> {
    const a = await this.repository.findByUserAndPeer(user, peer);
    const b = await this.repository.findByUserAndPeer(peer, user);

    return [a, b];
  }

  async accept(a: Relationship, b: Relationship) {
    a.type = RelationshipType.FRIEND;
    b.type = RelationshipType.FRIEND;

    await this.repository.save(a);
    await this.repository.save(b);

    await this.achievementProgressService.increment(Achievements.YOU, a.user);

    for (const user of [a.user, b.user]) {
      await this.achievementProgressService.increment(
        Achievements.SMALL_GROUP,
        user
      );
      await this.achievementProgressService.increment(
        Achievements.FOOTBALL_TEAM,
        user
      );
      await this.achievementProgressService.increment(Achievements.STAR, user);
      await this.achievementProgressService.increment(
        Achievements.WORLD_KNOWN,
        user
      );
    }

    this.socketService.broadcastUserRelationshipUpdate(a);
    this.socketService.broadcastUserRelationshipUpdate(b);
  }

  async block(a: Relationship, b: Relationship) {
    a.type = RelationshipType.BLOCK;

    await this.repository.save(a);
    await this.repository.delete(b);

    await this.achievementProgressService.increment(Achievements.NOPE, a.user);

    this.socketService.broadcastUserRelationshipUpdate(a);
    this.socketService.broadcastUserRelationshipDelete(a.peer, a.user);
  }

  async ask(user: User, peer: User) {
    const a = new Relationship();
    a.user = user;
    a.peer = peer;
    a.type = RelationshipType.OUTCOMING;

    const b = new Relationship();
    b.user = peer;
    b.peer = user;
    b.type = RelationshipType.INCOMING;

    await this.repository.save(a);
    await this.repository.save(b);

    await this.achievementProgressService.increment(
      Achievements.A_FRIEND_OUT,
      user
    );
    await this.achievementProgressService.increment(
      Achievements.A_FRIEND_IN,
      peer
    );

    this.socketService.broadcastUserRelationshipNew(a);
    this.socketService.broadcastUserRelationshipNew(b);

    return [a, b];
  }

  async blockUser(user: User, peer: User) {
    const a = new Relationship();
    a.user = user;
    a.peer = peer;
    a.type = RelationshipType.BLOCK;

    await this.repository.save(a);

    this.socketService.broadcastUserRelationshipUpdate(a);

    await this.achievementProgressService.increment(Achievements.NOPE, user);

    return a;
  }

  async delete(user: User, peer: User) {
    const [a, b] = await this.findRelationships(user, peer);

    if (a) {
      const { user, peer } = a;
      await this.repository.delete(a);

      this.socketService.broadcastUserRelationshipDelete(user, peer);

      if (a.type === RelationshipType.INCOMING) {
        await this.achievementProgressService.increment(Achievements.NOT_YOU, user);
      }
    }

    if (b && !b.isBlock()) {
      const { user, peer } = b;

      await this.repository.delete(b);

      this.socketService.broadcastUserRelationshipDelete(user, peer);
    }
  }
}
