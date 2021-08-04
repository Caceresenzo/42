import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import Achievement from "./Achievement";
import User from "./User";

@Entity({
  name: "achievement_progresses",
})
export default class AchievementProgress {
  @PrimaryGeneratedColumn()
  id: number;

  @ManyToOne(() => User, {
    onDelete: "CASCADE",
  })
  user: User;

  @ManyToOne(() => Achievement, {
    eager: true,
    onDelete: "CASCADE",
  })
  achievement: Achievement;

  @Column()
  value: number;

  @Column({ nullable: true })
  unlockedAt?: Date;

  get unlocked() {
    return !!this.unlockedAt;
  }

  public toJSON() {
    return {
      value: this.value,
      unlocked: this.unlocked,
      unlockedAt: this.unlockedAt,
      achievement: this.achievement.toJSON(),
    };
  }
}
