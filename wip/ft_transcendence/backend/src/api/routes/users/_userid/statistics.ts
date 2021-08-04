import * as express from "express";
import Container from "typedi";
import User from "../../../../entities/User";
import UserStatisticsService from "../../../../services/UserStatisticsService";
import middlewares from "../../../middlewares";

export default (app: express.Router) => {
  const userStatisticsService = Container.get(UserStatisticsService);

  const route = express.Router();

  app.use("/statistics", middlewares.authorize(false), route);

  route.get("/", async (req, res, next) => {
    const user: User = res.locals.user;

    try {
      const statistics = await userStatisticsService.getByUser(user);

      res.status(200).send(statistics);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
