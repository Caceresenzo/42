import * as express from "express";
import Maps from "../../../game/Maps";
import middlewares from "../../middlewares";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/maps", middlewares.authorize(false), route);

  route.get("/", (req, res, next) => {
    res.status(200).send(Maps.pool)
  })

  return route;
};
