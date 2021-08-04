import * as express from "express";
import { Container } from "typeorm-typedi-extensions";
import User from "../../../../../entities/User";
import OTPService from "../../../../../services/OTPService";

export default (app: express.Router) => {
  const otpService = Container.get(OTPService);

  const route = express.Router();

  app.use("/settings/otp", route);

  const sendStatus = (user: User, res: express.Response) => {
    res.status(200).send({
      enabled: user.otp,
      uri: otpService.generateURI(user),
    });
  };

  route.get("/", (req, res, next) => {
    const user: User = req.user as any;

    try {
      sendStatus(user, res);
    } catch (error) {
      next(error);
    }
  });

  route.post("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      await otpService.enable(user);

      sendStatus(user, res);
    } catch (error) {
      next(error);
    }
  });

  route.delete("/", async (req, res, next) => {
    const user: User = req.user as any;

    try {
      await otpService.disable(user);

      sendStatus(user, res);
    } catch (error) {
      next(error);
    }
  });

  return route;
};
