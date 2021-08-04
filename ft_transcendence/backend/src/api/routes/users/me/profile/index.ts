import * as express from "express";
import avatar from "./avatar";
import otp from "./otp";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/profile", route);

  avatar(route);
  otp(route);

  return route;
};
