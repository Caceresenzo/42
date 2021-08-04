import * as express from "express";
import middlewares from "../../middlewares";
import _peerid from "./_peerid";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/direct-messages", middlewares.authorize(false), route);

  _peerid(route);

  return route;
};
