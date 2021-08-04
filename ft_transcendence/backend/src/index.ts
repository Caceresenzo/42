import "reflect-metadata";

import * as express from "express";
import * as http from "http";
import config from "./config";

async function main() {
  const app = express();
  const server = http.createServer(app);

  await require("./loaders").default({
    app,
    server,
  });

  server.listen(config.PORT, () => {
    console.log(`Started http://localhost:${config.PORT}`);
  });
}

try {
  main();
} catch (error) {
  console.error(error);
}
