import { User } from "./User";

export interface Visit {
    id: number;
    user: User;
    date: string;
    times: number;
    firstAt: string;
    lastAt: string;
}