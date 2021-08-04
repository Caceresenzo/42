import * as express from "express";
import middlewares from "../../middlewares";
import _id from "./_id";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/matches", middlewares.authorize(false), route);

  _id(route);

  return route;
};
