import * as express from "express";
import * as fileUpload from "express-fileupload";
import Container from "typedi";
import User from "../../../../../entities/User";
import UserService from "../../../../../services/UserService";

export default (app: express.Router) => {
  const userService = Container.get(UserService);

  const route = express.Router();

  app.use("/avatar", route);

  route.post(
    "/",
    fileUpload(),
    async (req, res, next) => {
      const user: User = req.user as any;

      try {
        if (!req.files || !req.files.image) {
          throw new Error("missing `image` file");
        }

        if (Array.isArray(req.files.image)) {
          throw new Error("multiple `image` file");
        }

        const image: fileUpload.UploadedFile = req.files.image;

        await userService.updateAvatar(user, image);

        res.status(200).send(user.toJSON());
      } catch (error) {
        next(error);
      }
    },
    route
  );

  return route;
};
