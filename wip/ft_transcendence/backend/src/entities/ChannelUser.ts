import {
  Column,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
  Unique,
} from "typeorm";
import Channel from "./Channel";
import User from "./User";

@Unique(["channel", "user"])
@Entity({
  name: "channel_users",
})
export default class ChannelUser {
  @PrimaryGeneratedColumn()
  id: number;

  @ManyToOne(() => Channel, {
    onDelete: "CASCADE",
  })
  channel: Channel;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  user: User;

  @Column({
    default: false,
  })
  admin: boolean;

  @Column({
    default: false,
  })
  banned: boolean;

  @Column({
    default: false,
  })
  muted: boolean;

  @Column({
    nullable: true,
  })
  mutedUntil?: Date;

  public toJSON() {
    return {
      id: this.user.id,
      username: this.user.username,
      admin: this.admin,
      banned: this.banned,
      muted: this.muted,
      mutedUntil: this.mutedUntil,
    };
  }
}
