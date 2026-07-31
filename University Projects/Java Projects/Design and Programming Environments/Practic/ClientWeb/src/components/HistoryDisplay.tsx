import type { GameDTO } from '../types';
import { GameTable } from './GameTable';

interface HistoryDisplayProps {
  history: GameDTO[];
  error: string | null;
  loading: boolean;
}

export function HistoryDisplay({ history, error, loading }: HistoryDisplayProps) {
  if (history.length > 0) {
    return (
      <>
        {history.map((game, gameIndex) => (
          <GameTable key={gameIndex} game={game} />
        ))}
      </>
    );
  }

  if (history.length === 0 && !error && !loading) {
    return <p>Nu există date de afișat.</p>;
  }

  return null;
}
