import * as express from "express";
import Container from "typedi";
import Channel from "../../../../../entities/Channel";
import ChannelService from "../../../../../services/ChannelService";
import middlewares from "../../../../middlewares";

export default (app: express.Router) => {
  const channelService = Container.get(ChannelService);

  const route = express.Router();

  app.use(
    "/:channelid",
    middlewares.simplePathVariable("channelid", "channel", async (id) => {
      return await channelService.findById(id);
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const channel: Channel = res.locals.channel;

    try {
      res.status(200).send(channel.toJSON());
    } catch (error) {
      next(error);
    }
  });

  return route;
};
