import * as express from "express";
import * as celebrate from "celebrate";
import Container from "typedi";
import ChannelService from "../../../services/ChannelService";
import Channel, {
  Visibility as ChannelVisibility,
} from "../../../entities/Channel";
import middlewares from "../../middlewares";
import _id from "./_id";
import User from "../../../entities/User";

export default (app: express.Router) => {
  const channelService = Container.get(ChannelService);

  const route = express.Router();

  app.use("/channels", middlewares.authorize(false), route);

  route.get("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      let channels: Array<Channel>;
      if (user.admin) {
        channels = await channelService.allNotDirect();
      } else {
        channels = await channelService.allNotPrivate();
      }

      res.status(200).send(channels);
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
          password: celebrate.Joi.string()
            .min(8)
            .max(20)
            .when("visibility", {
              is: celebrate.Joi.equal(ChannelVisibility.PROTECTED),
              then: celebrate.Joi.required(),
              otherwise: celebrate.Joi.forbidden(),
            }),
        },
      },
      {
        abortEarly: false,
      }
    ),
    async (req, res, next) => {
      const user: User = req.user as any;
      const { name, visibility, password } = req.body as {
        name: string;
        visibility: ChannelVisibility;
        password?: string;
      };

      try {
        const channel = new Channel();
        channel.owner = user;
        channel.name = name;
        channel.visibility = visibility;
        channel.password = password;

        await channel.updatePasswordHash();
        await channelService.create(channel);

        res.status(200).send(channel.toJSON());
      } catch (error) {
        next(error);
      }
    }
  );

  _id(route);

  return route;
};
