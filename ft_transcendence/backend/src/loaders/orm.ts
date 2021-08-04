import { useContainer, createConnection } from "typeorm";
import { Container } from "typedi";

export default async () => {
  useContainer(Container);
  
  await createConnection();
};
