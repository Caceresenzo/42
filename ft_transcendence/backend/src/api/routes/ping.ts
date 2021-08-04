import * as express from "express";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/ping", route);

  route.use("/", (req, res, next) => {
    res.status(200).send("pong");
  });

  return route;
};
