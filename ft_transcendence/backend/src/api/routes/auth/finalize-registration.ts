import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typedi";
import User from "../../../entities/User";
import UserService from "../../../services/UserService";
import helpers from "../../helpers";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const userService = Container.get(UserService);

  const route = express.Router();

  app.use("/finalize-registration", route);

  route.post(
    "/",
    middlewares.authorize(false),
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        username: celebrate.Joi.string().min(4).max(20).required(),
      },
    }),
    async (req, res, next) => {
      const user: User = req.user as any;
      const { username }: { username: string } = req.body;

      try {
        if (user.doneFirstStep) {
          return helpers.forbidden("already done");
        }

        const changed = await userService.firstStep(user, username);
        if (!changed) {
          return helpers.conflict("username taken");
        }

        res.status(200).send(user);
      } catch (error) {
        next(error);
      }
    }
  );

  return route;
};
