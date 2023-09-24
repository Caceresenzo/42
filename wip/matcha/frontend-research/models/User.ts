export enum Gender {
    MAN = "MAN",
    WOMAN = "WOMAN",
}

export enum SexualOrientation {
    HETERO = "HETERO",
    HOMO = "HOMO",
    BI = "BI",
}

export interface User {
    id: number;
    login: string;
    email: string;
    firstName: string;
    lastName: string;
    biography?: string;
    gender?: Gender;
    sexualOrientation?: SexualOrientation;
    emailConfirmed: boolean;
    emailConfirmedAt: string | null;
}