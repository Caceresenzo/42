import * as express from "express";
import * as celebrate from "celebrate";
import Container from "typedi";
import User from "../../../../../entities/User";
import RelationshipService from "../../../../../services/RelationshipService";
import Relationship, {
  Type as RelationshipType,
} from "../../../../../entities/Relationship";
import UserService from "../../../../../services/UserService";
import helpers from "../../../../helpers";
import _peerid from "./_peerid";

export default (app: express.Router) => {
  const relationshipService = Container.get(RelationshipService);
  const userService = Container.get(UserService);

  const route = express.Router();

  app.use("/relationships", route);

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      const relationships = await relationshipService.all(user);

      res.status(200).send(relationships);
    } catch (error) {
      next(error);
    }
  });

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        peerId: celebrate.Joi.number().required(),
        type: celebrate.Joi.string()
          .valid(RelationshipType.FRIEND, RelationshipType.BLOCK)
          .required(),
      },
    }),
    async (req, res, next) => {
      const user: User = req.user as any;
      const { peerId, type } = req.body as {
        peerId: number;
        type: RelationshipType;
      };

      try {
        const peer = await userService.findById(peerId);

        if (!peer) {
          return helpers.notFound("peer not found");
        }

        const [a, b] = await relationshipService.findRelationships(user, peer);

        let result = a;

        if (b && b.type == RelationshipType.BLOCK) {
          return helpers.forbidden("user blocked you");
        }

        if (a && a.type == RelationshipType.BLOCK) {
          return helpers.forbidden("you have blocked user");
        }

        if (a && a.type == RelationshipType.INCOMING) {
          if (type == RelationshipType.FRIEND) {
            await relationshipService.accept(a, b);
          } else {
            await relationshipService.block(a, b);
            result = a;
          }
        }

        if (a && a.type == RelationshipType.OUTCOMING) {
          if (type == RelationshipType.BLOCK) {
            await relationshipService.block(a, b);
          }
        }

        if (a?.type == RelationshipType.FRIEND && b?.type == RelationshipType.FRIEND) {
          if (type == RelationshipType.FRIEND) {
            /* no op */
          } else {
            await relationshipService.block(a, b);
            result = a;
          }
        }

        if (!b && !a) {
          if (type == RelationshipType.FRIEND) {
            const [a2, b2] = await relationshipService.ask(user, peer);
            result = a2;
          } else {
            result = await relationshipService.blockUser(user, peer);
          }
        }

        res.status(200).send(result);
      } catch (error) {
        next(error);
      }
    }
  );

  _peerid(route);

  return route;
};
