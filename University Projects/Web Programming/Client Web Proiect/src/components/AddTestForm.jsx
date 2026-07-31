import { useState } from 'react';

export default function AddTestForm({ onAdd }) {
    const [distance, setDistance] = useState('');
    const [style, setStyle] = useState('');

    const handleSubmit = (e) => {
        e.preventDefault();
        if (!distance || !style) {
            alert('Te rog completează ambele câmpuri!');
            return;
        }

        onAdd({ distance: parseInt(distance), style });

        setDistance('');
        setStyle('');
    }

    return (
        <div style={{ marginTop: '20px', padding: '15px', border: '1px solid #ccc', borderRadius: '5px' }}>
            <h3>Adaugă o probă nouă</h3>
            <form onSubmit={handleSubmit}>
                <input 
                    type="number" 
                    placeholder="Distanța (m)" 
                    value={distance} 
                    onChange={(e) => setDistance(e.target.value)} 
                    style={{ marginRight: '10px' }}
                />
                <input 
                    type="text" 
                    placeholder="Stil (ex: Liber)" 
                    value={style} 
                    onChange={(e) => setStyle(e.target.value)} 
                    style={{ marginRight: '10px' }}
                />
                <button type="submit">Adaugă Probă</button>
            </form>
        </div>
    );
}