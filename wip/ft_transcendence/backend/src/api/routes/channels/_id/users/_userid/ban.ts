import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import ChannelUser from "../../../../../../entities/ChannelUser";
import User from "../../../../../../entities/User";
import ChannelUserService from "../../../../../../services/ChannelUserService";
import helpers from "../../../../../helpers";

export default (app: express.Router) => {
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use("/ban", route);

  function update(to: boolean) {
    const action = to ? "ban" : "unban";

    const errorNotAdmin = `only admin can ${action}`;
    const errorAdminItself = `admin cannot ${action} itself`;

    return async (
      req: express.Request,
      res: express.Response,
      next: express.NextFunction
    ) => {
      const user: User = req.user as any;
      const selfChannelUser: ChannelUser = res.locals.selfChannelUser;
      const channelUser: ChannelUser = res.locals.channelUser;

      try {
        if (!user.admin) {
          if (!selfChannelUser.admin) {
            return helpers.forbidden(errorNotAdmin);
          }

          if (selfChannelUser.user.id === channelUser.user.id) {
            return helpers.forbidden(errorAdminItself);
          }
        }

        await channelUserService.setBanned(channelUser, to);

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
