import * as celebrate from "celebrate";
import * as express from "express";
import Container from "typedi";
import User from "../../../../entities/User";
import UserService from "../../../../services/UserService";
import helpers from "../../../helpers";
import middlewares from "../../../middlewares";
import matches from "./matches";
import achievements from "./achievements";
import avatar from "./avatar";
import statistics from "./statistics";
import game from "./game";
import friends from "./friends";

export default (app: express.Router) => {
  const userService = Container.get(UserService);

  const route = express.Router();

  app.use(
    "/:userid",
    celebrate.celebrate({
      [celebrate.Segments.PARAMS]: {
        userid: celebrate.Joi.number().required(),
      },
    }),
    async (req, res, next) => {
      const id = Number(req.params.userid);

      try {
        const user = await userService.findById(id);
        res.locals.user = user;

        if (!user) {
          return helpers.notFound("user not found");
        }

        next();
      } catch (error) {
        next(error);
      }
    },
    route
  );

  route.get("/", middlewares.authorize(false), async (req, res, next) => {
    const user: User = res.locals.user;

    try {
      res.status(200).send(user.toJSON());
    } catch (error) {
      next(error);
    }
  });

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        banned: celebrate.Joi.boolean().optional(),
      },
    }),
    middlewares.authorize(true),
    async (req, res, next) => {
      const user: User = res.locals.user;

      const { banned }: { banned?: boolean } = req.body;

      try {
        if (banned !== undefined) {
          await userService.setBanned(user, banned);
        }

        res.status(200).send(user.toJSON());
      } catch (error) {
        next(error);
      }
    }
  );

  achievements(route);
  avatar(route);
  matches(route);
  statistics(route);
  game(route);
  friends(route);

  return route;
};
