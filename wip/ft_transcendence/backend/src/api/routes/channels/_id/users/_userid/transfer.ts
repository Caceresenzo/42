import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import Channel from "../../../../../../entities/Channel";
import ChannelUser from "../../../../../../entities/ChannelUser";
import User from "../../../../../../entities/User";
import ChannelService from "../../../../../../services/ChannelService";
import helpers from "../../../../../helpers";

export default (app: express.Router) => {
  const channelService = Container.get(ChannelService);

  const route = express.Router();

  app.use("/transfer", route);

  route.post("/", async (req, res, next) => {
    const user: User = req.user as any;
    const channel: Channel = res.locals.channel;
    const channelUser: ChannelUser = res.locals.channelUser;

    try {
      if (!user.admin) {
        if (user.id !== channel.owner.id) {
          return helpers.forbidden("only owner can transfer ownership");
        }
      }

      await channelService.transferOwnership(channel, channelUser);

      res.status(200).send(channel);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
