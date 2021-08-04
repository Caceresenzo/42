import { Strategy as OAuthStrategy } from "./types";

import * as OAuth2Strategy from "passport-oauth2";

export const BASE_API_URL = "https://api.intra.42.fr";

export const AUTHORIZATION_URL = BASE_API_URL + "/v2/oauth/authorize";
export const TOKEN_URL = BASE_API_URL + "/oauth/token"; /* does not work */

export const PROFILE_API_URL = BASE_API_URL + "/v2/me";

export const Strategy: OAuthStrategy = function(options, verify) {
  const strategy = new OAuth2Strategy.Strategy(
    {
      authorizationURL: AUTHORIZATION_URL,
      tokenURL: TOKEN_URL,
      clientID: options.clientID,
      clientSecret: options.clientSecret,
      callbackURL: options.callbackURL,
    },
    verify
  );

  strategy.userProfile = function (accesstoken, done) {
    this._oauth2._request(
      "GET",
      PROFILE_API_URL,
      null,
      null,
      accesstoken,
      (err, data) => {
        if (err) {
          return done(err);
        }

        try {
          data = JSON.parse(data);
        } catch (e) {
          return done(e);
        }
        
        done(null, data);
      }
    );
  };

  return strategy;
}
