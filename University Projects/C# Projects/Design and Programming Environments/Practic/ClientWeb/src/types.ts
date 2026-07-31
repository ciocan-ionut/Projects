export interface Category {
    name: string;
    answers: {
        text: string;
        points: number;
    }[];
}