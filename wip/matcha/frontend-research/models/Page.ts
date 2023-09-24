export interface Page<T> {
    content: Array<T>;
    totalElements: number;
    first: boolean;
    last: boolean;
    pageNumber: number;
    totalPages: number;
    pageSize: number;
}
