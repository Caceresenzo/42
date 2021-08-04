import * as express from "express";
import Container from "typedi";
import Achievement from "../../../entities/Achievement";
import AchievementService from "../../../services/AchievementService";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const achievementService = Container.get(AchievementService);

  const route = express.Router();

  app.use(
    "/:id",
    middlewares.simplePathVariable("id", "achievement", async (id) => {
      return await achievementService.findById(id);
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const achievement: Achievement = res.locals.achievement;

    try {
      res.status(200).send(achievement);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
