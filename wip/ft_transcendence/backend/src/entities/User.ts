import { Column, Entity, Index, PrimaryGeneratedColumn } from "typeorm";
import databaseExtra from "../config/database-extra";

@Entity({
  name: "users",
  engine: databaseExtra.UTF8,
})
export default class User {
  @PrimaryGeneratedColumn()
  id: number;

  @Index({ unique: true })
  @Column()
  username: string;

  @Index({ unique: true })
  @Column()
  email: string;

  @Column({ default: false })
  admin: boolean;

  @Column({ default: false })
  banned: boolean;

  @Column()
  picture: string;

  @Column({ default: false })
  otp: boolean;

  @Column({ nullable: true })
  otpSecret?: string;

  @Column({ default: false })
  doneFirstStep: boolean;

  public toJSON() {
    return {
      id: this.id,
      username: this.username,
      admin: this.admin,
      banned: this.banned,
      picture: this.picture,
      doneFirstStep: this.doneFirstStep ? undefined : false,
    };
  }

  public toRoom() {
    return `user_${this.id}`;
  }

  public is(other: User) {
    return this.id === other?.id;
  }
}
