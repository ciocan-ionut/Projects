import type { GameDTO } from '../types';

interface GameTableProps {
  game: GameDTO;
}

export function GameTable({ game }: GameTableProps) {
  return (
    <div style={{ marginBottom: '20px' }}>
      <h2>Joc ID: {game.gameId} - Total Rounds: {game.totalRounds}</h2>
      <table border={1} cellPadding={10} style={{ marginTop: '20px', width: '100%', borderCollapse: 'collapse' }}>
        <thead>
          <tr style={{ backgroundColor: '#f2f2f2' }}>
            <th>Runda</th>
            <th>Punctaj</th>
            <th>Poziție</th>
          </tr>
        </thead>
        <tbody>
          {game.playerRoundDetails?.map((round, index) => (
            <tr key={index}>
              <td>{round.roundNo}</td>
              <td>{round.score}</td>
              <td>{round.position}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
