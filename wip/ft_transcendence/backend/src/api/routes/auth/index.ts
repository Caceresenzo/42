import * as express from "express";
import finalizeRegistration from "./finalize-registration";
import oauth from "./oauth";
import refreshToken from "./refresh-token";
import unlock from "./unlock";

export default (app: express.Router) => {
  const route = express.Router();

  app.use("/auth", route);

  oauth(route);
  refreshToken(route);
  unlock(route);
  finalizeRegistration(route);

  return route;
};
