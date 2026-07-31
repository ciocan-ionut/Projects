interface SearchSectionProps {
  username: string;
  onUsernameChange: (value: string) => void;
  onFetch: () => void;
  loading: boolean;
}

export function SearchSection({ username, onUsernameChange, onFetch, loading }: SearchSectionProps) {
  return (
    <div className="search-section">
      <input 
        type="text" 
        value={username} 
        onChange={(e) => onUsernameChange(e.target.value)} 
        placeholder="Introdu alias-ul..."
      />
      <button onClick={onFetch} disabled={loading}>
        {loading ? 'Se caută...' : 'Caută Istoric'}
      </button>
    </div>
  );
}
