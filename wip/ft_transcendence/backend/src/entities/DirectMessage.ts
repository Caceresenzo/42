import {
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
  Unique,
} from "typeorm";
import Channel from "./Channel";
import User from "./User";

@Unique(["user", "peer"])
@Entity({
  name: "direct_messages",
})
export default class DirectMessage {
  @PrimaryGeneratedColumn()
  id: number;

  @ManyToOne(() => Channel, {
    eager: true,
    onDelete: "CASCADE",
  })
  channel: Channel;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  user: User;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  peer: User;

  public toJSON() {
    return {
      channel: this.channel,
      peer: this.peer,
    };
  }
}
