import * as celebrate from "celebrate";
import { NextFunction, Request, Response } from "express";
import helpers from "../helpers";

export function pathVariable(
  variableName: string,
  handler: (
    variable: number,
    req: Request,
    res: Response,
    next: NextFunction
  ) => any
) {
  return [
    celebrate.celebrate({
      [celebrate.Segments.PARAMS]: {
        [variableName]: celebrate.Joi.number().required(),
      },
    }),
    async (req: Request, res: Response, next: NextFunction) => {
      try {
        const variable = Number(req.params[variableName]);

        await handler(variable, req, res, next);
      } catch (error) {
        next(error);
      }
    },
  ];
}

export function simplePathVariable(
  variableName: string,
  toLocal: string,
  handler: (variable: number, req: Request, res: Response) => any
) {
  return [
    celebrate.celebrate({
      [celebrate.Segments.PARAMS]: {
        [variableName]: celebrate.Joi.number().required(),
      },
    }),
    async (req: Request, res: Response, next: NextFunction) => {
      const variable = Number(req.params[variableName]);

      try {
        const model = await handler(variable, req, res);

        if (!model) {
          helpers.notFound(
            `no ${toLocal} found with ${variableName} = ${variable}`
          );
        }

        res.locals[toLocal] = model;

        next();
      } catch (error) {
        next(error);
      }
    },
  ];
}
