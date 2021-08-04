import * as express from "express";
import Container from "typedi";
import Achievement from "../../../entities/Achievement";
import AchievementService from "../../../services/AchievementService";
import _id from "./_id";

export default (app: express.Router) => {
  const achievementService = Container.get(AchievementService);

  const route = express.Router();

  app.use("/achievements", route);

  route.get("/", async (req, res, next) => {
    try {
      const achievements: Array<Achievement> = await achievementService.all();

      res.status(200).send(achievements);
    } catch (error) {
      next(error);
    }
  });

  _id(route);

  return route;
};
