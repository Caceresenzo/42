import { Column, CreateDateColumn, Entity, Index, ManyToOne, PrimaryGeneratedColumn } from "typeorm";
import User from "./User";

export enum Phase {
  TWO_FACTOR = "2fa",
}

@Entity({
  name: "phase_tokens",
})
export default class PhaseToken {
  @PrimaryGeneratedColumn()
  id: number;

  @Column({
    type: "enum",
    enum: Phase,
    default: Phase.TWO_FACTOR,
  })
  phase: Phase;

  @ManyToOne(() => User, {
    eager: true,
    nullable: true,
    onDelete: "CASCADE",
  })
  user: User;

  @Index({ unique: true })
  @Column()
  token: string;

  @CreateDateColumn()
  createdAt: Date;

  public is2Factor(): boolean {
    return this.phase === Phase.TWO_FACTOR;
  }

  public toJSON() {
    return {
      phase: this.phase,
      user: this.user,
      token: this.token,
    };
  }

  static Phase = Phase;
}
