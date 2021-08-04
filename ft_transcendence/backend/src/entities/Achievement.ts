import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity({
  name: "achievements",
})
export default class Achievement {
  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  name: string;

  @Column()
  description: string;

  @Column()
  percent: boolean;

  @Column()
  max: number;

  public toJSON() {
    return {
      id: this.id,
      name: this.name,
      description: this.description,
      percent: this.percent,
      max: this.max,
    };
  }
}
