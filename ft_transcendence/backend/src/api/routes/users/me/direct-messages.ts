import * as express from "express";
import Container from "typedi";
import Channel from "../../../../entities/Channel";
import User from "../../../../entities/User";
import ChannelService from "../../../../services/ChannelService";
import DirectMessageService from "../../../../services/DirectMessageService";

export default (app: express.Router) => {
  const directMessageService = Container.get(DirectMessageService);

  const route = express.Router();

  app.use("/direct-messages", route);

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      const directMessages = await directMessageService.findAllByUser(user);

      res.status(200).send(directMessages);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
