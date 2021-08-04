import {
  Column,
  Entity,
  ManyToOne,
  PrimaryGeneratedColumn,
  Unique,
} from "typeorm";
import User from "./User";

export enum Type {
  FRIEND = "friend",
  BLOCK = "block",
  INCOMING = "incoming",
  OUTCOMING = "outcoming",
}

@Entity({
  name: "relationships",
})
@Unique(["user", "peer"])
export default class Relationship {
  @PrimaryGeneratedColumn()
  id: number;

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

  @Column({
    type: "enum",
    enum: Type,
  })
  type: Type;

  public isBlock() {
    return this.type === Type.BLOCK;
  }

  public toJSON() {
    return {
      type: this.type,
      peer: {
        id: this.peer.id,
        username: this.peer.username,
      },
    };
  }
}
