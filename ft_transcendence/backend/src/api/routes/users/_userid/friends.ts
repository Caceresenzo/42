import * as express from "express";
import Container from "typedi";
import User from "../../../../entities/User";
import RelationshipService from "../../../../services/RelationshipService";
import middlewares from "../../../middlewares";

export default (app: express.Router) => {
  const relationshipService = Container.get(RelationshipService);

  const route = express.Router();

  app.use("/friends", middlewares.authorize(false), route);

  route.get("/", async (req, res, next) => {
    const user: User = res.locals.user;

    try {
      const friends = await relationshipService.findAllFriends(user);

      res.status(200).send(friends);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
