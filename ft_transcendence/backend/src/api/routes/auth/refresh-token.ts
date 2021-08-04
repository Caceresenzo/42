import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typedi";
import AuthService from "../../../services/AuthService";

export default (app: express.Router) => {
  const authService = Container.get(AuthService);

  const route = express.Router();

  app.use("/refresh-token", route);

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        accessToken: celebrate.Joi.string().required(),
        refreshToken: celebrate.Joi.string().required(),
      },
    }),
    async (req, res, next) => {
      try {
        const tokens = await authService.refresh(req.body.refreshToken);

        res.status(200).send(tokens);
      } catch (error) {
        next(error);
      }
    }
  );

  return route;
};
