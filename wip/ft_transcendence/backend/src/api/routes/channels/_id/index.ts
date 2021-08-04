import { ValidationError } from "@hapi/joi";
import * as celebrate from "celebrate";
import * as express from "express";
import Container from "typedi";
import Channel, {
  Visibility as ChannelVisibility,
} from "../../../../entities/Channel";
import User from "../../../../entities/User";
import ChannelService from "../../../../services/ChannelService";
import ChannelUserService from "../../../../services/ChannelUserService";
import helpers from "../../../helpers";
import middlewares from "../../../middlewares";
import messages from "./messages";
import users from "./users";

export default (app: express.Router) => {
  const channelService = Container.get(ChannelService);
  const channelUserService = Container.get(ChannelUserService);

  const route = express.Router();

  app.use(
    "/:id",
    middlewares.pathVariable("id", async (id, req, res, next) => {
      const user: User = req.user as any;

      try {
        const channel = await channelService.findById(id);

        if (!channel) {
          return helpers.notFound(`no channel found with id: ${id}`);
        }

        const selfChannelUser = await channelUserService.findByChannelAndUser(
          channel,
          user
        );

        if (selfChannelUser) {
          selfChannelUser.channel = channel; /* cache channel instance */
        }

        if (user.admin) {
          if (!selfChannelUser && channel.isDirect()) {
            return helpers.forbidden("direct channel");
          }
        } else {
          if (selfChannelUser?.banned) {
            return helpers.forbidden("banned");
          }

          if (!channel.isPublic() && !selfChannelUser) {
            return helpers.forbidden(channel.visibility);
          }
        }

        res.locals.channel = channel;
        res.locals.selfChannelUser = selfChannelUser;

        next();
      } catch (error) {
        next(error);
      }
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

  route.post(
    "/",
    celebrate.celebrate(
      {
        [celebrate.Segments.BODY]: {
          name: celebrate.Joi.string().min(3).max(20).required(),
          visibility: celebrate.Joi.string()
            .valid(
              ChannelVisibility.PUBLIC,
              ChannelVisibility.PROTECTED,
              ChannelVisibility.PRIVATE
            )
            .required(),
          password: celebrate.Joi.string().min(8).max(20).optional(),
        },
      },
      {
        abortEarly: false,
      }
    ),
    async (req, res, next) => {
      const user: User = req.user as any;
      const channel: Channel = res.locals.channel;

      const { name, visibility, password } = req.body as {
        name: string;
        visibility: ChannelVisibility;
        password?: string;
      };

      try {
        if (!user.admin) {
          if (channel.owner.id !== user.id) {
            return helpers.forbidden("only owner can edit channel");
          }
        }

        if (channel.isDirect()) {
          return helpers.forbidden("direct channel cannot be edited");
        }

        if (
          !channel.isProtected() &&
          visibility === ChannelVisibility.PROTECTED &&
          !password
        ) {
          return helpers.bad(
            "changing to a protected channel require a password"
          );
        }

        channel.name = name;
        channel.visibility = visibility;
        channel.password = password;

        await channel.updatePasswordHash();
        await channelService.update(channel);

        res.status(200).send(channel.toJSON());
      } catch (error) {
        next(error);
      }
    }
  );

  route.delete("/", async (req, res, next) => {
    const user: User = req.user as any;
    const channel: Channel = res.locals.channel;

    try {
      if (!user.admin) {
        if (channel.owner.id !== user.id) {
          return helpers.forbidden("only owner can delete channel");
        }
      }

      if (channel.isDirect()) {
        return helpers.forbidden("direct channel cannot be deleted");
      }

      await channelService.delete(channel);

      res.status(204).end();
    } catch (error) {
      next(error);
    }
  });

  users(route);
  messages(route);

  return route;
};
