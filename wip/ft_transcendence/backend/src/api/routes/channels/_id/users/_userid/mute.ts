import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import ChannelUser from "../../../../../../entities/ChannelUser";
import User from "../../../../../../entities/User";
import ChannelUserService from "../../../../../../services/ChannelUserService";
import helpers from "../../../../../helpers";

export default (app: express.Router) => {
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use("/mute", route);

  function update(to: boolean) {
    const action = to ? "mute" : "unmute";

    const errorNotAdmin = `only admin can ${action}`;

    const handler = async (
      req: express.Request,
      res: express.Response,
      next: express.NextFunction
    ) => {
      const user: User = req.user as any;
      const selfChannelUser: ChannelUser = res.locals.selfChannelUser;
      const channelUser: ChannelUser = res.locals.channelUser;

      const { duration } = req.body as { duration: number | null };

      try {
        if (!user.admin) {
          if (!selfChannelUser.admin) {
            return helpers.forbidden(errorNotAdmin);
          }
        }

        await channelUserService.setMuted(channelUser, to, duration);

        res.status(200).send(channelUser);
      } catch (error) {
        next(error);
      }
    };

    if (to) {
      return [
        celebrate.celebrate(
          {
            [celebrate.Segments.BODY]: {
              duration: celebrate.Joi.number()
                .greater(0)
                .allow(null)
                .required(),
            },
          },
          {
            abortEarly: false,
          }
        ),
        handler,
      ];
    }

    return handler;
  }

  route.post("/", update(true));
  route.delete("/", update(false));

  return route;
};
