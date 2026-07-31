import { useState } from 'react';
import axios from 'axios';
import type { Category } from './types';
import './App.css';
import { ErrorMessage } from './components/ErrorMessage';
import { AddSection } from './components/AddSection';

function App() {
  const [error, setError] = useState<string | null>(null);
  const [loading, setLoading] = useState(false);

  const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:5029/api/game/answer';

  const postCategory = async (category: Category) => {
    setLoading(true);
    setError(null);

    try {
      const response = await axios.post<Category>(`${API_URL}`, category);

      alert(response.data);
    } catch (err: unknown) {
      console.error(err);
      if (axios.isAxiosError(err)) {
        setError(err.response?.data || 'A apărut o eroare la conectarea cu serverul.');
      } else if (err instanceof Error) {
        setError(err.message);
      } else {
        setError('A apărut o eroare necunoscută.');
      }
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container">
      <h1>Istoric Jucător</h1>
      
      <AddSection onPost={postCategory} loading={loading} />

      <ErrorMessage error={error} />
    </div>
  );
}

export default App;