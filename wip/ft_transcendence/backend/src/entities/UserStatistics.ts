import {
  Column,
  Entity,
  JoinColumn,
  OneToOne,
  PrimaryGeneratedColumn,
} from "typeorm";
import User from "./User";

@Entity({
  name: "user_statitics",
})
export default class UserStatitics {
  @PrimaryGeneratedColumn()
  id: number;

  @OneToOne(() => User, {
    onDelete: "CASCADE",
  })
  @JoinColumn()
  user: User;

  @Column({ default: 0 })
  winCount: number;

  @Column({ default: 0 })
  lossCount: number;

  public toJSON() {
    return {
      winCount: this.winCount,
      lossCount: this.lossCount,
    };
  }
}
