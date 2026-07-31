import { useState } from 'react';
import type { Category } from "../types";

interface AddSectionProps {
    onPost: (category: Category) => void;
    loading: boolean;
}

export function AddSection({ onPost, loading }: AddSectionProps) {
    const [categoryName, setCategoryName] = useState('');
    const [answerText, setAnswerText] = useState('');
    const [answerPoints, setAnswerPoints] = useState(0);

    const onAdd = () => {
        const category: Category = {
            name: categoryName,
            answers: [
                {
                    text: answerText,
                    points: answerPoints
                }
            ]
        };
        onPost(category);
    };

    return (
        <div>
            <input
                type="text"
                placeholder="Category Name"
                value={categoryName}
                onChange={(e) => setCategoryName(e.target.value)}
            />
            <input
                type="text"
                placeholder="Answer Text"
                value={answerText}
                onChange={(e) => setAnswerText(e.target.value)}
            />
            <input
                type="number"
                placeholder="Answer Points"
                value={answerPoints}
                onChange={(e) => setAnswerPoints(parseInt(e.target.value, 10) || 0)}
            />
            <button onClick={onAdd} disabled={loading}>
                Add
            </button>
        </div>
    );
}