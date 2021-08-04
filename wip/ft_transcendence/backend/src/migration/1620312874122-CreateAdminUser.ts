import { Service } from "typedi";
import { getRepository, MigrationInterface, QueryRunner } from "typeorm";
import User from "../entities/User";

@Service()
export class CreateAdminUser1620312874122 implements MigrationInterface {
  public async up(queryRunner: QueryRunner): Promise<void> {
    const user = new User();

    user.username = "caceresenzo1502";
    user.email = "caceresenzo1502@gmail.com";
    user.admin = true;

    const userRepository = getRepository(User);

    await userRepository.save(user);
  }

  public async down(queryRunner: QueryRunner): Promise<void> {}
}
