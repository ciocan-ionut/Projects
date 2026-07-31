export default function Toolbar({ onFilterChange, handleLogout }) {
    return (
        <div style={{ marginBottom: '20px', padding: '10px', backgroundColor: '#f0f0f0', borderRadius: '5px' }}>
            <label style={{ marginRight: '10px', fontWeight: 'bold' }}>Filtrează după stil:</label>
            <select onChange={(e) => onFilterChange(e.target.value)}>
                <option value="">Toate</option>
                <option value="liber">Liber</option>
                <option value="spate">Spate</option>
                <option value="bras">Bras</option>
                <option value="fluture">Fluture</option>
            </select>

            <button onClick={handleLogout}>Logout</button>
        </div>
    );
}