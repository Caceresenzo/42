import { Container } from "typedi";
import Achievement from "../entities/Achievement";
import AchievementService from "../services/AchievementService";

function inline(object: Partial<Achievement>) {
  const achievement = new Achievement();

  Object.assign(achievement, object);

  return achievement;
}

export default class Achievements {
  static REGISTERED = inline({
    id: 1000,
    name: "Registered!",
    description: "Create an account",
    percent: true,
    max: 1,
  });

  static COMMUNITY_MEMBER = inline({
    id: 2000,
    name: "Community Member",
    description: "Send 100 messages",
    percent: true,
    max: 100,
  });

  static COMMUNITY_CREATOR = inline({
    id: 2100,
    name: "Community Creator",
    description: "Create a channel",
    percent: false,
    max: 1,
  });

  static COMMUNITY_GROWER = inline({
    id: 2200,
    name: "Community Grower",
    description: "Invite someone to a channel",
    percent: false,
    max: 1,
  });

  static ONE_OF_US = inline({
    id: 2300,
    name: "One of us!",
    description: "Join a protected channel",
    percent: false,
    max: 1,
  });

  static BEGINNER = inline({
    id: 3000,
    name: "Beginner",
    description: "Play your first game",
    percent: false,
    max: 1,
  });

  static INTERMEDIATE = inline({
    id: 3100,
    name: "Intermediate",
    description: "Play 10 game",
    percent: false,
    max: 10,
  });

  static GAMER = inline({
    id: 3200,
    name: "Gamer",
    description: "Play 100 game",
    percent: false,
    max: 100,
  });

  static GO_OUTSIDE = inline({
    id: 3300,
    name: "Go Outside!",
    description: "Play 1000 game",
    percent: false,
    max: 1000,
  });

  static FIRST_TIME = inline({
    id: 4000,
    name: "First time",
    description: "Win a game for the first time",
    percent: false,
    max: 1,
  });

  static KING_OF_THE_HILL = inline({
    id: 4100,
    name: "King of the Hill",
    description: "Win 10 games",
    percent: false,
    max: 10,
  });

  static AT_WHAT_COST = inline({
    id: 4200,
    name: "i've won...... but at what cost?",
    description: "Win 100 games",
    percent: false,
    max: 100,
  });

  static NOPE = inline({
    id: 5000,
    name: "Nope!",
    description: "Block someone",
    percent: false,
    max: 1,
  });

  static NOT_YOU = inline({
    id: 5100,
    name: "Not you!",
    description: "Refuse someone friend request",
    percent: false,
    max: 1,
  });

  static YOU = inline({
    id: 5200,
    name: "You!",
    description: "Accept someone friend request",
    percent: false,
    max: 1,
  });

  static A_FRIEND_OUT = inline({
    id: 5300,
    name: "A friend: out",
    description: "Send a friend request",
    percent: false,
    max: 1,
  });

  static A_FRIEND_IN = inline({
    id: 5400,
    name: "A friend: in",
    description: "Receive a friend request",
    percent: false,
    max: 1,
  });

  static SMALL_GROUP = inline({
    id: 6000,
    name: "Small group",
    description: "Have 3 friends",
    percent: false,
    max: 3,
  });

  static FOOTBALL_TEAM = inline({
    id: 6100,
    name: "Football Team",
    description: "Have 11 friends",
    percent: false,
    max: 11,
  });

  static STAR = inline({
    id: 6200,
    name: "Star",
    description: "Have 100 friends",
    percent: false,
    max: 100,
  });

  static WORLD_KNOWN = inline({
    id: 6300,
    name: "World Known",
    description: "Have 1000 friends",
    percent: false,
    max: 1000,
  });

  static HELLO = inline({
    id: 7000,
    name: "Hello",
    description: "Speak to someone",
    percent: false,
    max: 1,
  });

  static CHALLENGER = inline({
    id: 7100,
    name: "Challenger",
    description: "Challenge to someone",
    percent: false,
    max: 1,
  });

  static async install() {
    const achievementService = Container.get(AchievementService);

    for (const value of Object.values(Achievements)) {
      if (!(value instanceof Achievement)) {
        continue;
      }

      await achievementService.save(value);
    }
  }
}
