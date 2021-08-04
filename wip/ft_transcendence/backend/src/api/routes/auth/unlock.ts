import * as celebrate from "celebrate";
import * as express from "express";
import { Container } from "typedi";
import { Phase } from "../../../entities/PhaseToken";
import AuthService from "../../../services/AuthService";
import OTPService from "../../../services/OTPService";
import PhaseTokenService from "../../../services/PhaseTokenService";
import helpers from "../../helpers";

export default (app: express.Router) => {
  const phaseTokenService = Container.get(PhaseTokenService);
  const otpService = Container.get(OTPService);
  const authService = Container.get(AuthService);

  const route = express.Router();

  app.use("/unlock", route);

  route.post(
    "/",
    celebrate.celebrate({
      [celebrate.Segments.BODY]: {
        token: celebrate.Joi.string().required(),
        phase: celebrate.Joi.string().valid(Phase.TWO_FACTOR).required(),
        otp: celebrate.Joi.string().when("phase", {
          is: celebrate.Joi.equal(Phase.TWO_FACTOR),
          then: celebrate.Joi.required(),
          otherwise: celebrate.Joi.forbidden(),
        }),
      },
    }),
    async (req, res, next) => {
      const {
        token,
        phase,
        otp,
      }: {
        token: string;
        phase: Phase;
        otp?: string;
      } = await req.body;

      try {
        const phaseToken = await phaseTokenService.findByTokenAndPhase(
          token,
          phase
        );

        if (!phaseToken) {
          return helpers.notFound("no phase token found");
        }

        const { user } = phaseToken;

        await phaseTokenService.delete(phaseToken);

        switch (phase) {
          case Phase.TWO_FACTOR: {
            if (!otpService.check(user, otp)) {
              return helpers.forbidden("invalid otp");
            }

            res.status(200).send(await authService.authenticate(user));
            break;
          }

          default: {
            throw Error("unexpected phase: " + phase);
          }
        }
      } catch (error) {
        next(error);
      }
    }
  );

  return route;
};
