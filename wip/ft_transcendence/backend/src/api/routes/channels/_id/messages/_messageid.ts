import * as express from "express";
import Container from "typedi";
import ChannelMessage from "../../../../../entities/ChannelMessage";
import ChannelMessageService from "../../../../../services/ChannelMessageService";
import middlewares from "../../../../middlewares";

export default (app: express.Router) => {
  const channelMessageService = Container.get(ChannelMessageService);

  const route = express.Router();

  app.use(
    "/:messageid",
    middlewares.simplePathVariable(
      "messageid",
      "channelMessage",
      async (id) => {
        return await channelMessageService.findById(id);
      }
    ),
    route
  );

  route.get("/", async (_req, res, next) => {
    const channelMessage: ChannelMessage = res.locals.channelMessage;

    try {
      res.status(200).send(channelMessage);
    } catch (error) {
      next(error);
    }
  });

  route.delete("/", async (_req, res, next) => {
    const channelMessage: ChannelMessage = res.locals.channelMessage;

    try {
      await channelMessageService.delete(channelMessage);

      res.status(204).end();
    } catch (error) {
      next(error);
    }
  });

  return route;
};
