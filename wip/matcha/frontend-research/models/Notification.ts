export interface Notification {
    id: number;
    type: string;
    content: string;
    link: string | null;
    createdAt: string;
    read: boolean;
    readAt: string | null;
}