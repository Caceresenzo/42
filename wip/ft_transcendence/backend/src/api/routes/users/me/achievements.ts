import * as express from "express";
import Container from "typedi";
import User from "../../../../entities/User";
import AchievementProgressService from "../../../../services/AchievementProgressService";

export default (app: express.Router) => {
  const achievementProgressService = Container.get(AchievementProgressService);

  const route = express.Router();

  app.use("/achievements", route);

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      const achievementProgresses = await achievementProgressService.allByUser(
        user
      );

      res.status(200).send(achievementProgresses);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
