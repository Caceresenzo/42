import * as express from "express";
import * as http from "http";
import ormLoader from "./orm";
import expressLoader from "./express";
import socketioLoader from "./socket-io";
import Achievements from "../game/Achievements";
import cronLoader from "./cron";
import { Container } from "typeorm-typedi-extensions";
import AvatarService from "../services/AvatarService";

function makeErrorJSONCompatible() {
  if (!("toJSON" in Error.prototype))
    Object.defineProperty(Error.prototype, "toJSON", {
      value: function () {
        var alt = {};

        Object.getOwnPropertyNames(this).forEach(function (key) {
          alt[key] = this[key];
        }, this);

        return alt;
      },
      configurable: true,
      writable: true,
    });
}

export default async ({
  app,
  server,
}: {
  app: express.Application;
  server: http.Server;
}) => {
  makeErrorJSONCompatible();

  await ormLoader();
  await expressLoader({ app });
  await socketioLoader({ server });
  await cronLoader();

  await Achievements.install();
  await Container.get(AvatarService).install();
};
