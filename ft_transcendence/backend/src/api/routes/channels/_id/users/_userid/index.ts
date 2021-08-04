import * as express from "express";
import Container from "typedi";
import Channel from "../../../../../../entities/Channel";
import ChannelUser from "../../../../../../entities/ChannelUser";
import User from "../../../../../../entities/User";
import ChannelUserService from "../../../../../../services/ChannelUserService";
import helpers from "../../../../../helpers";
import middlewares from "../../../../../middlewares";
import admin from "./admin";
import ban from "./ban";
import mute from "./mute";
import transfer from "./transfer";

export default (app: express.Router) => {
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use(
    "/:userid",
    middlewares.simplePathVariable(
      "userid",
      "channelUser",
      async (id, _req, res) => {
        const channel: Channel = res.locals.channel;
        const user: User = { id } as User;

        const channelUser: ChannelUser =
          await channelUserService.findByChannelAndUser(channel, user);

        if (channelUser) {
          channelUser.channel = channel; /* cache channel instance */
        }

        return channelUser;
      }
    ),
    route
  );

  route.get("/", async (req, res, next) => {
    const channelUser: ChannelUser = res.locals.channelUser;

    try {
      res.status(200).send(channelUser);
    } catch (error) {
      next(error);
    }
  });

  route.delete("/", async (req, res, next) => {
    const user: User = req.user as any;
    const channel: Channel = res.locals.channel;
    const selfChannelUser: ChannelUser = res.locals.selfChannelUser;
    const channelUser: ChannelUser = res.locals.channelUser;

    try {
      if (channel.owner.id === channelUser.user.id) {
        return helpers.forbidden("owner cannot leave");
      }

      if (!user.admin) {
        if (user.id !== channelUser.user.id) {
          if (!selfChannelUser.admin) {
            return helpers.forbidden("you are not an admin");
          }

          /* admin kick */
        } else if (channelUser.banned) {
          return helpers.forbidden("banned");
        } /* else {
          self leave
        } */
      }

      channelUserService.delete(channelUser);

      res.status(204).end();
    } catch (error) {
      next(error);
    }
  });

  admin(route);
  ban(route);
  mute(route);
  transfer(route);

  return route;
};
