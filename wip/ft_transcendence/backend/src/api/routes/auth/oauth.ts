import * as celebrate from "celebrate";
import * as express from "express";
import * as passport from "passport";
import { Container } from "typedi";
import { Phase } from "../../../entities/PhaseToken";
import User from "../../../entities/User";
import AuthService from "../../../services/AuthService";
import OAuthService from "../../../services/OAuthService";
import PhaseTokenService from "../../../services/PhaseTokenService";
import helpers from "../../helpers";

function oauth(route: express.Router, name: string, scopes: string[]) {
  const phaseTokenService = Container.get(PhaseTokenService);
  const authService = Container.get(AuthService);

  route.get(
    `/${name}`,
    passport.authenticate(name, {
      session: false,
      scope: scopes,
    })
  );

  route.get(
    `/${name}/callback`,
    celebrate.celebrate({
      [celebrate.Segments.QUERY]: {
        code: celebrate.Joi.string().required(),
      },
    }),
    (req, res, next) => {
      passport.authenticate(name, async (err, user: User, info) => {
        try {
          if (err) {
            throw err;
          }

          if (user.banned) {
            throw helpers.forbidden("banned");
          }

          if (user.otp) {
            const phaseToken = await phaseTokenService.create(
              user,
              Phase.TWO_FACTOR
            );

            res.status(402).send(phaseToken);
          } else {
            const tokens = await authService.authenticate(user);

            res.status(200).send(tokens);
          }
        } catch (error) {
          next(error);
        }
      })(req, res, next);
    }
  );
}

export default (app: express.Router) => {
  const oauthService = Container.get(OAuthService);

  const route = express.Router();

  app.use("/oauth", route);

  oauth(route, "google", ["profile", "email"]);
  oauth(route, "marvin", ["public"]);

  oauthService.install();

  return route;
};
