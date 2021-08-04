import {
  Column,
  Entity,
  Index,
  ManyToOne,
  PrimaryGeneratedColumn,
} from "typeorm";
import User from "./User";

@Entity({
  name: "refresh_tokens",
})
export default class RefreshToken {
  @PrimaryGeneratedColumn()
  id: number;

  @ManyToOne(() => User, {
    onDelete: "CASCADE",
  })
  user: User;

  @Index({ unique: true })
  @Column()
  token: string;

  @Index()
  @Column()
  expires: Date;

  @Index()
  @Column()
  created: Date = new Date();

  @Index()
  @Column({ nullable: true })
  revoked?: Date;

  public get expired() {
    return new Date() >= this.expires;
  }

  public get active() {
    return !this.revoked && !this.expired;
  }
}
