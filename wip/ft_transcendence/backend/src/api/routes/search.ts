import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import Channel from "../../entities/Channel";
import User from "../../entities/User";
import SearchService from "../../services/SearchService";
import { UserEvent } from "../../services/SocketService";

export default (app: express.Router) => {
  const searchService = Container.get(SearchService);

  const route = express.Router();

  app.use(
    "/search",
    celebrate.celebrate({
      [celebrate.Segments.QUERY]: {
        query: celebrate.Joi.string().required(),
      },
    }),
    route
  );

  route.get("/", async (req, res, next) => {
    const query: string = req.query.query as string;

    try {
      const results: { [key: string]: any[] } = await searchService.searchAll(
        query
      );

      res.status(200).send(results);
    } catch (error) {
      next(error);
    }
  });

  route.get("/users", async (req, res, next) => {
    const query: string = req.query.query as string;

    try {
      const results: Array<User> = await searchService.search(User, query);

      res.status(200).send(results);
    } catch (error) {
      next(error);
    }
  });

  route.get("/channels", async (req, res, next) => {
    const query: string = req.query.query as string;

    try {
      const results: Array<Channel> = await searchService.search(Channel, query);

      res.status(200).send(results);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
