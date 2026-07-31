import { useState } from 'react';

export default function Table({ tests, onDelete, onUpdate, isAuthenticated }) {
    const [editingId, setEditingId] = useState(null);
    const [editedDistance, setEditedDistance] = useState('');
    const [editedStyle, setEditedStyle] = useState('');

    const handleEdit = (test) => {
        setEditingId(test.id);
        setEditedDistance(test.distance);
        setEditedStyle(test.style);
    }

    const handleCancel = () => {
        setEditingId(null);
    }

    const handleSave = (id) => {
        if (!editedDistance || !editedStyle) {
            alert('Te rog completează ambele câmpuri!');
            return;
        }
        onUpdate(id, { distance: parseInt(editedDistance), style: editedStyle });
        setEditingId(null);
    }

    return (
        <table border="1" cellPadding="10" style={{ width: '100%', borderCollapse: 'collapse', textAlign: 'left' }}>
            <thead style={{ backgroundColor: '#ddd' }}>
                <tr>
                    <th>ID</th>
                    <th>Distanță (m)</th>
                    <th>Stil</th>
                    { isAuthenticated && <th>Acțiuni</th> }
                </tr>
            </thead>
            <tbody>
                {tests.map((test) => (
                    <tr key={test.id}>
                        <td>{test.id}</td>
                        {editingId === test.id ? (
                            <>
                                <td>
                                    <input 
                                        type="number" 
                                        value={editedDistance} 
                                        onChange={(e) => setEditedDistance(e.target.value)} 
                                    />
                                </td>
                                <td>
                                    <input 
                                        type="text" 
                                        value={editedStyle} 
                                        onChange={(e) => setEditedStyle(e.target.value)} 
                                    />
                                </td>
                                <td>
                                    <>
                                        <button onClick={() => handleSave(test.id)} style={{ marginRight: '5px', color: 'green' }}>Save</button>
                                        <button onClick={handleCancel} style={{ color: 'red' }}>Cancel</button>
                                    </>
                                </td>
                            </>
                        ) : (
                            <>
                                <td>{test.distance}</td>
                                <td>{test.style}</td>
                                { isAuthenticated && 
                                    <td>
                                        <>
                                            <button onClick={() => handleEdit(test)} style={{ marginRight: '5px' }}>Edit</button>
                                            <button onClick={() => onDelete(test.id)}>Delete</button>
                                        </>
                                    </td>
                                }
                            </>
                        )}
                    </tr>
                ))}
                {tests.length === 0 && (
                    <tr>
                        <td colSpan="4" style={{ textAlign: 'center' }}>Nu există probe de afișat.</td>
                    </tr>
                )}
            </tbody>
        </table>
    );
}