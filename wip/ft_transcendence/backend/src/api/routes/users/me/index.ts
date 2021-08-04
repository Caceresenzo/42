import * as express from "express";
import channels from "./channels";
import achievements from "./achievements";
import relationships from "./relationships";
import middlewares from "../../../middlewares";
import profile from "./profile";
import directMessages from "./direct-messages";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/@me", middlewares.authorize(false), route);

  route.get("/", (req, res, next) => {
    try {
      res.status(200).send(req.user);
    } catch (error) {
      next(error);
    }
  });

  achievements(route);
  relationships(route);
  channels(route);
  profile(route);
  directMessages(route);

  return route;
};
