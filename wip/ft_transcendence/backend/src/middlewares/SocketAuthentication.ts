import * as jsonwebtoken from "jsonwebtoken";
import { Middleware, MiddlewareInterface } from "socket-controllers";
import Container from "typedi";
import config from "../config";
import UserService from "../services/UserService";

export default () => {
  const userService = Container.get(UserService);

  return async (socket: any, next: (err?: any) => any) => {
    const { accessToken } = socket.handshake.auth;

    try {
      const payload: any = jsonwebtoken.verify(accessToken, config.JWT_SECRET);

      const user = await userService.findById(payload.id);

      if (!user) {
        throw new Error("user not found");
      }

      socket.data.user = user;
      next();
    } catch (error) {
      next(error);
    }
  };
};
