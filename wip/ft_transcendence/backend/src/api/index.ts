import { Router } from "express";

import auth from "./routes/auth";
import users from "./routes/users";
import channels from "./routes/channels";
import achievements from "./routes/achievements";
import search from "./routes/search";
import directMessages from "./routes/direct-messages";
import pendingGames from "./routes/pending-games";
import matches from "./routes/matches";
import maps from "./routes/maps";
import ping from "./routes/ping";

export default () => {
  const app = Router();

  auth(app);
  users(app);
  channels(app);
  achievements(app);
  directMessages(app);
  pendingGames(app);
  search(app);
  matches(app);
  maps(app);
  ping(app);

  return app;
};
