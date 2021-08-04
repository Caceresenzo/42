import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import User from "../../../../../../entities/User";
import Channel from "../../../../../../entities/Channel";
import ChannelUser from "../../../../../../entities/ChannelUser";
import ChannelUserService from "../../../../../../services/ChannelUserService";
import helpers from "../../../../../helpers";

export default (app: express.Router) => {
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use("/admin", route);

  function update(to: boolean) {
    const action = to ? "promote" : "demote";

    const errorNotOwner = `only owner can ${action}`;
    const errorOwnerItself = `owner cannot ${action} itself`;

    return async (
      req: express.Request,
      res: express.Response,
      next: express.NextFunction
    ) => {
      const user: User = req.user as any;
      const channel: Channel = res.locals.channel;
      const channelUser: ChannelUser = res.locals.channelUser;

      try {
        if (!user.admin) {
          if (channel.owner.id !== user.id) {
            return helpers.forbidden(errorNotOwner);
          }
  
          if (channel.owner.id === channelUser.user.id) {
            return helpers.forbidden(errorOwnerItself);
          }
        }

        await channelUserService.setAdmin(channelUser, to);

        res.status(200).send(channelUser);
      } catch (error) {
        next(error);
      }
    };
  }

  route.post("/", update(true));
  route.delete("/", update(false));

  return route;
};
