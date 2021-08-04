import * as celebrate from "celebrate";
import * as express from "express";
import Container from "typedi";
import User from "../../../../../entities/User";
import RelationshipService from "../../../../../services/RelationshipService";
import UserService from "../../../../../services/UserService";
import helpers from "../../../../helpers";

export default (app: express.Router) => {
  const userService = Container.get(UserService);
  const relationshipService = Container.get(RelationshipService);

  const route = express.Router();

  app.use(
    "/:peerid",
    celebrate.celebrate({
      [celebrate.Segments.PARAMS]: {
        peerid: celebrate.Joi.number().required(),
      },
    }),
    async (req, res, next) => {
      const id = Number(req.params.peerid);

      try {
        const peer = await userService.findById(id);
        res.locals.peer = peer;

        if (!peer) {
          return helpers.notFound("peer not found");
        }

        next();
      } catch (error) {
        next(error);
      }
    },
    route
  );

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;
    const peer: User = res.locals.peer;

    try {
      const relationship = await relationshipService.findRelationship(
        user,
        peer
      );

      res.status(200).send(relationship);
    } catch (error) {
      next(error);
    }
  });

  route.delete("/", async (req, res, next) => {
    const user: User = req.user as any;
    const peer: User = res.locals.peer;

    try {
      await relationshipService.delete(user, peer);

      res.status(204).end();
    } catch (error) {
      next(error);
    }
  });

  return route;
};
