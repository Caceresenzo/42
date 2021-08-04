import * as express from "express";
import * as cors from "cors";
import * as morgan from "morgan";
import * as passport from "passport";
import * as celebrate from "celebrate";

import routes from "../api";

export default async ({ app }: { app: express.Application }) => {
  app.get("/status", (req, res) => {
    res.status(200).end();
  });

  app.enable("trust proxy");
  app.disable('etag');

  app.use(morgan("tiny"));

  app.use(cors());

  app.use((req, res, next) => {
    res.header("Content-Type", "application/json");
    next();
  });

  app.use(express.json());
  app.use(express.urlencoded({ extended: true }));

  app.use(passport.initialize());

  app.use(routes());

  app.use((req, res, next) => {
    const err = new Error("not found");
    err["status"] = 404;
    next(err);
  });

  app.use((err, req, res, next) => {
    if (celebrate.isCelebrateError(err)) {
      const validation = {};

      for (const [segment, joiError] of err.details.entries()) {
        validation[segment] = {
          source: segment,
          fields: joiError.details.map((detail) => ({
            message: detail.message,
            path: detail.path.join('.')
          })),
        };
      }

      return res.status(400).send({ validation });
    } else if (err.name === "UnauthorizedError") {
      return res.status(err.status).send({ message: err.message });
    } else if (err.name === "AuthError") {
      return res.status(401).send({ message: err.message });
    }

    return next(err);
  });

  app.use((err, req, res, next) => {
    res.status(err.status || 500);
    res.send({
      errors: {
        message: err.message,
      },
    });
  });
};
