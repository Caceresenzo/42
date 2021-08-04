import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import { Side } from "../game/Enums";
import User from "./User";

@Entity({
  name: "matches",
})
export default class Match {
  @PrimaryGeneratedColumn()
  id: number;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  player1: User;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  player2: User;

  @Column({
    default: false,
  })
  score1: number;

  @Column({
    default: false,
  })
  score2: number;

  @ManyToOne(() => User, {
    eager: true,
    onDelete: "CASCADE",
  })
  winner: User;

  public toJSON() {
    return {
      id: this.id,
      player: {
        [Side.LEFT]: {
          user: this.player1,
          score: this.score1,
        },
        [Side.RIGHT]: {
          user: this.player2,
          score: this.score2,
        },
      },
      winner: this.winner,
    };
  }
}
