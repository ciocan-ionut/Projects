export default function LoginForm({ setUsername, setPassword, handleLogin }) {
    return (
        <div>
            <h2>Login</h2>
            <form onSubmit={handleLogin} style={{ margin: '20px 0' }}>
              <input placeholder="Username" onChange={e => setUsername(e.target.value)} />
              <input type="password" placeholder="Password" onChange={e => setPassword(e.target.value)} />
              <button type="submit">Autentificare</button>
            </form>
        </div>
    );
}