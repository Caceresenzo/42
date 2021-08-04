import * as OAuth2Strategy from "passport-oauth2";

export interface StrategyOptions {
  clientID: string;
  clientSecret: string;
  callbackURL?: string;
}

export type Strategy = (
  options: StrategyOptions,
  verify: OAuth2Strategy.VerifyFunction
) => OAuth2Strategy.Strategy;
