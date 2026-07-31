import { useState, useEffect } from "react";
import Toolbar from "./components/Toolbar";
import Table from "./components/Table";
import AddTestForm from "./components/AddTestForm";
import { Client } from "@stomp/stompjs";
import SockJS from "sockjs-client/dist/sockjs";
import LoginForm from "./components/LoginForm";

const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:8081/api/probe';
const LOGIN_API_URL = import.meta.env.VITE_LOGIN_API_URL || 'http://localhost:8081/api/auth/login';

export default function App() {
  const [tests, setTests] = useState([]);
  const [filter, setFilter] = useState('');
  const [refreshTrigger, setRefreshTrigger] = useState(0);

  const [token, setToken] = useState(localStorage.getItem('jwt') || '');
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');

  const handleLogin = async (e) => {
    e.preventDefault();
    const res = await fetch(LOGIN_API_URL, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password })
    });

    if (res.ok) {
      const jwtToken = await res.text();
      setToken(jwtToken);
      localStorage.setItem('jwt', jwtToken);
    } else {
      alert("Login failed!");
    }
  }

  const handleLogout = () => {
    setToken('');
    localStorage.removeItem('jwt');
  }

  useEffect(() => {
    if (!token) return;

    const stompClient = new Client({
      webSocketFactory: () => new SockJS('http://localhost:8081/ws'),
      onConnect: () => {
        console.log("WebSocket connected");
        stompClient.subscribe('/topic/swimmingTests', (message) => {
          console.log("Received WebSocket message:", message.body);
          setRefreshTrigger(prev => prev + 1);
        });
      }
    });

    stompClient.activate();
    return () => stompClient.deactivate();
  }, [token]);

  useEffect(() => {
    const fetchTests = async () => {
      try {
        let url = API_URL;
        if (filter) {
          url += `?style=${filter}`;
        }
        const response = await fetch(url);
        const data = await response.json();
        setTests(data);
      } catch (error) {
        console.error('Eroare la preluarea datelor:', error);
      }
    };
    fetchTests();
  }, [filter, refreshTrigger]);

  const handleAdd = async (newTest) => {
    try {
      await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json', 'Authorization': `Bearer ${token}` },
        body: JSON.stringify(newTest)
      });
      // setRefreshTrigger(prev => prev + 1);
    } catch (error) {
      console.error("Eroare la adăugare:", error);
    }
  };

  const handleUpdate = async (id, updatedData) => {
    try {
      await fetch(`${API_URL}/${id}`, {
        method: 'PUT',
        headers: { 'Content-Type': 'application/json', 'Authorization': `Bearer ${token}` },
        body: JSON.stringify(updatedData)
      });
      // setRefreshTrigger(prev => prev + 1);
    } catch (error) {
      console.error("Eroare la modificare:", error);
    }
  };

  const handleDelete = async (id) => {
    if (window.confirm("Sigur vrei să ștergi proba cu ID-ul " + id + "?")) {
      try {
        await fetch(`${API_URL}/${id}`, {
          method: 'DELETE',
          headers: { 'Authorization': `Bearer ${token}` }
        });
        // setRefreshTrigger(prev => prev + 1);
      } catch (error) {
        console.error("Eroare la stergere:", error);
      }
    }
  };

  return (
    <div style={{ maxWidth: '800px', margin: '0 auto', padding: '20px', fontFamily: 'sans-serif' }}>
      <h1>Aplicație Probe Înot</h1>
      
      <LoginForm setUsername={setUsername} setPassword={setPassword} handleLogin={handleLogin} />

      <Toolbar onFilterChange={setFilter} handleLogout={handleLogout} />

      <Table 
        tests={tests} 
        onDelete={handleDelete} 
        onUpdate={handleUpdate} 
        isAuthenticated={!!token}
      />

      {token && <AddTestForm onAdd={handleAdd} /> }
    </div>
  );
}