import * as dotenv from "ts-dotenv";

export default dotenv.load({
  PORT: {
    type: Number,
    default: 3001,
  },
  GOOGLE_ID: String,
  GOOGLE_SECRET: String,
  MARVIN_ID: String,
  MARVIN_SECRET: String,
  OAUTH_BASE_CALLBACK_URL: {
    type: String,
    default: "http://localhost:3000",
  },
  JWT_SECRET: String,
  JWT_ALGORITHM: {
    type: String,
    default: "HS256",
  },
  JWT_EXPIRATION: {
    type: String,
    default: "15m",
  },
  REFRESH_TOKEN_LENGTH: {
    type: Number,
    default: 40,
  },
  PHASE_TOKEN_LENGTH: {
    type: Number,
    default: 80,
  },
  MATCHMAKING_ONLY_ONE: {
    type: Boolean,
    default: false,
  },
} as const);
