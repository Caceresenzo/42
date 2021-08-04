import * as express from "express";
import Container from "typedi";
import User from "../../../../entities/User";
import MatchService from "../../../../services/MatchService";
import middlewares from "../../../middlewares";

export default (app: express.Router) => {
  const matchService = Container.get(MatchService);

  const route = express.Router();

  app.use("/matches", middlewares.authorize(false), route);

  route.get("/", async (req, res, next) => {
    const user: User = res.locals.user;

    try {
      const matches = await matchService.findAllByUser(user);

      res.status(200).send(matches);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
