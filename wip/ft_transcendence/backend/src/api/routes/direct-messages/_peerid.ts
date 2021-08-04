import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import User from "../../../entities/User";
import DirectMessageService from "../../../services/DirectMessageService";
import UserService from "../../../services/UserService";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const userService = Container.get(UserService);
  const directMessageService = Container.get(DirectMessageService);

  const route = express.Router();

  app.use(
    "/:peerid",
    middlewares.simplePathVariable("peerid", "peer", async (id) => {
      return await userService.findById(id);
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;
    const peer: User = res.locals.peer;

    try {
      const directMessage = await directMessageService.getOrCreate(user, peer);

      res.status(200).send(directMessage);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
