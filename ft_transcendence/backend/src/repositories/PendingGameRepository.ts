import { Service } from "typedi";
import { EntityRepository, Repository } from "typeorm";
import PendingGame from "../entities/PendingGame";

@Service()
@EntityRepository(PendingGame)
export default class PendingGameRepository extends Repository<PendingGame> {}
