import * as cron from "node-cron";
import { Container } from "typeorm-typedi-extensions";
import ChannelUserService from "../services/ChannelUserService";

export default async () => {
  const channelUserService = Container.get(ChannelUserService)
  
  cron.schedule("*/10 * * * * *", () => {
    channelUserService.unmuteAllIfPassed()
  });
};
