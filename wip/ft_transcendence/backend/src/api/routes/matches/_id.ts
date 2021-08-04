import * as express from "express";
import Container from "typedi";
import Match from "../../../entities/Match";
import MatchService from "../../../services/MatchService";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const matchService = Container.get(MatchService);

  const route = express.Router();

  app.use(
    "/:id",
    middlewares.simplePathVariable("id", "match", async (id) => {
      return await matchService.findById(id);
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const match: Match = res.locals.match;

    try {
      res.status(200).send(match);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
