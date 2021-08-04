import * as express from "express";
import * as celebrate from "celebrate";
import Container from "typedi";
import Channel from "../../../../../entities/Channel";
import ChannelUserService from "../../../../../services/ChannelUserService";
import _userid from "./_userid";
import UserService from "../../../../../services/UserService";
import helpers from "../../../../helpers";
import User from "../../../../../entities/User";
import ChannelUser from "../../../../../entities/ChannelUser";

export default (app: express.Router) => {
  const userService = Container.get(UserService);
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use("/users", route);

  route.get("/", async (req, res, next) => {
    const channel: Channel = res.locals.channel;
    const users = await channelUserService.allByChannel(channel);

    res.status(200).send(users);
  });

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        userId: celebrate.Joi.number().required(),
      },
    }),
    async (req, res, next) => {
      const currentUser: User = req.user as any;

      const userId: number = req.body.userId;

      const channel: Channel = res.locals.channel;

      try {
        const user: User = await userService.findById(userId);

        if (!user) {
          helpers.notFound("user not found");
        }

        let channelUser: ChannelUser =
          await channelUserService.findByChannelAndUser(channel, user);

        if (!channelUser) {
          channelUser = await channelUserService.create(
            channel,
            user,
            false,
            currentUser
          );
        }

        res.status(200).send(channelUser);
      } catch (error) {
        next(error);
      }
    }
  );

  _userid(route);

  return route;
};
