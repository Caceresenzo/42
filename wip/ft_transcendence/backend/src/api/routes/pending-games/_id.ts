import * as express from "express";
import Container from "typedi";
import Match from "../../../entities/Match";
import PendingGame from "../../../entities/PendingGame";
import PendingGameService from "../../../services/PendingGameService";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const pendingGameService = Container.get(PendingGameService);

  const route = express.Router();

  app.use(
    "/:id",
    middlewares.simplePathVariable("id", "pendingGame", async (id) => {
      return await pendingGameService.findById(id);
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const pendingGame: PendingGame = res.locals.pendingGame;

    try {
      res.status(200).send(pendingGame);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
