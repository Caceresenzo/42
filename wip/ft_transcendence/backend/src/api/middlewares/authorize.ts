import { NextFunction, Request, Response } from "express";
import * as expressJwt from "express-jwt";
import { Container } from "typeorm-typedi-extensions";

import config from "../../config";
import UserService from "../../services/UserService";

const authorize = (onlyAdmin = false) => [
  expressJwt({
    secret: config.JWT_SECRET,
    algorithms: [config.JWT_ALGORITHM],
  }),
  async (req: Request, res: Response, next: NextFunction) => {
    const userService = Container.get(UserService);

    const user = await userService.findById(req.user.id);

    if (!user || user.banned || (onlyAdmin && !user.admin)) {
      return res.status(401).json({
        message: "unauthorized",
        authenticated: !!user,
        banned: user?.banned || false,
      });
    }

    req.user = user;

    next();
  },
];

export default authorize;
