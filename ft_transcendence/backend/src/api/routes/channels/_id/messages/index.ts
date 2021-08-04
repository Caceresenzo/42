import * as celebrate from "celebrate";
import * as express from "express";
import Container from "typedi";
import Channel from "../../../../../entities/Channel";
import ChannelMessage from "../../../../../entities/ChannelMessage";
import ChannelUser from "../../../../../entities/ChannelUser";
import User from "../../../../../entities/User";
import ChannelMessageService from "../../../../../services/ChannelMessageService";
import helpers from "../../../../helpers";

export default (app: express.Router) => {
  const channelMessageService = Container.get(ChannelMessageService);

  const route = express.Router();

  app.use("/messages", route);

  route.get("/", async (req, res, next) => {
    const channel: Channel = res.locals.channel;

    try {
      const messages = await channelMessageService.allByChannel(channel);

      res.status(200).send(messages);
    } catch (error) {
      next(error);
    }
  });

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        type: celebrate.Joi.string().valid(ChannelMessage.Type.TEXT).required(),
        content: celebrate.Joi.string().min(1).max(200).required(),
      },
    }),
    async (req, res, next) => {
      const channel: Channel = res.locals.channel;
      const selfChannelUser: ChannelUser = res.locals.selfChannelUser;
      const user: User = req.user as any;

      try {
        if (selfChannelUser.muted) {
          return helpers.forbidden("muted");
        }

        const { type, content } = req.body;

        const message = new ChannelMessage();
        message.channel = Promise.resolve(channel);
        message.user = user;
        message.type = type;
        message.content = content;

        await channelMessageService.create(message);

        res.status(200).send(message);
      } catch (error) {
        next(error);
      }
    }
  );

  route.delete("/", async (req, res, next) => {
    const channel: Channel = res.locals.channel;
    const user: User = req.user as any;

    try {
      if (!user.admin && !user.is(channel.owner)) {
        return helpers.forbidden("only owner can clear messages");
      }

      await channelMessageService.deleteAllByChannel(channel);

      res.status(204).end();
    } catch (error) {
      next(error);
    }
  });

  return route;
};
