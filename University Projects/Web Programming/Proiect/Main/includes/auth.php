<?php

declare(strict_types=1);

function current_user(): ?array
{
    return $_SESSION['user'] ?? null;
}

function is_logged_in(): bool
{
    return current_user() !== null;
}

function require_login(): void
{
    if (!is_logged_in()) {
        header('Location: login.php');
        exit;
    }
}

function require_role(array $roles): void
{
    $user = current_user();

    if (!$user || !in_array($user['role'], $roles, true)) {
        http_response_code(403);
        echo 'Acces interzis.';
        exit;
    }
}

function authenticate_user(string $username, string $password): ?array
{
    $stmt = db_pdo()->prepare('SELECT users.id, users.username, users.password_hash, users.full_name, roles.name AS role FROM users INNER JOIN roles ON roles.id = users.role_id WHERE users.username = :username LIMIT 1');
    $stmt->execute(['username' => $username]);
    $user = $stmt->fetch();

    if (!$user || !password_verify($password, $user['password_hash'])) {
        return null;
    }

    return $user;
}

function login_user(array $user): void
{
    session_regenerate_id(true);
    $_SESSION['user'] = [
        'id' => (int) $user['id'],
        'username' => $user['username'],
        'full_name' => $user['full_name'],
        'role' => $user['role'],
    ];
}

function remember_user(int $userId): void
{
    $selector = bin2hex(random_bytes(16));
    $validator = bin2hex(random_bytes(32));
    $expiresAt = (new DateTimeImmutable(sprintf('+%d days', REMEMBER_ME_DAYS)))->format('Y-m-d H:i:s');

    $stmt = db_pdo()->prepare('INSERT INTO remember_tokens (user_id, selector, token_hash, expires_at) VALUES (:user_id, :selector, :token_hash, :expires_at)');
    $stmt->execute([
        'user_id' => $userId,
        'selector' => $selector,
        'token_hash' => hash('sha256', $validator),
        'expires_at' => $expiresAt,
    ]);

    setcookie(
        REMEMBER_ME_COOKIE,
        $selector . ':' . $validator,
        [
            'expires' => time() + (REMEMBER_ME_DAYS * 86400),
            'path' => '/',
            'secure' => !empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off',
            'httponly' => true,
            'samesite' => 'Lax',
        ]
    );
}

function auto_login_from_remember_cookie(): void
{
    if (is_logged_in() || empty($_COOKIE[REMEMBER_ME_COOKIE])) {
        return;
    }

    $parts = explode(':', (string) $_COOKIE[REMEMBER_ME_COOKIE], 2);
    if (count($parts) !== 2) {
        return;
    }

    [$selector, $validator] = $parts;
    $stmt = db_pdo()->prepare('SELECT remember_tokens.user_id, remember_tokens.token_hash, users.username, users.full_name, roles.name AS role FROM remember_tokens INNER JOIN users ON users.id = remember_tokens.user_id INNER JOIN roles ON roles.id = users.role_id WHERE remember_tokens.selector = :selector AND remember_tokens.expires_at > CURRENT_TIMESTAMP LIMIT 1');
    $stmt->execute(['selector' => $selector]);
    $token = $stmt->fetch();

    if (!$token || !hash_equals($token['token_hash'], hash('sha256', $validator))) {
        return;
    }

    login_user([
        'id' => $token['user_id'],
        'username' => $token['username'],
        'full_name' => $token['full_name'],
        'role' => $token['role'],
    ]);
}

function clear_remember_cookie(): void
{
    setcookie(REMEMBER_ME_COOKIE, '', [
        'expires' => time() - 3600,
        'path' => '/',
        'secure' => !empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off',
        'httponly' => true,
        'samesite' => 'Lax',
    ]);
}

function revoke_remember_token_for_user(int $userId): void
{
    $stmt = db_pdo()->prepare('DELETE FROM remember_tokens WHERE user_id = :user_id');
    $stmt->execute(['user_id' => $userId]);
}

function logout_user(): void
{
    if (!empty($_SESSION['user']['id'])) {
        revoke_remember_token_for_user((int) $_SESSION['user']['id']);
    }

    unset($_SESSION['user']);
    if (session_status() === PHP_SESSION_ACTIVE) {
        session_regenerate_id(true);
    }
}

function register_user(string $username, string $fullName, string $passwordHash): ?array
{
    $pdo = db_pdo();

    $stmt = $pdo->prepare('SELECT id FROM roles WHERE name = :role_name LIMIT 1');
    $stmt->execute(['role_name' => 'client']);
    $role = $stmt->fetch();

    if (!$role) {
        return null;
    }

    $stmt = $pdo->prepare('INSERT INTO users (role_id, username, password_hash, full_name) VALUES (:role_id, :username, :password_hash, :full_name)');
    try {
        $stmt->execute([
            'role_id' => $role['id'],
            'username' => $username,
            'password_hash' => $passwordHash,
            'full_name' => $fullName,
        ]);
        return ['id' => (int) $pdo->lastInsertId(), 'username' => $username, 'full_name' => $fullName, 'role' => 'client'];
    } catch (PDOException $e) {
        if (strpos((string) $e->getMessage(), 'Duplicate entry') !== false || strpos((string) $e->getMessage(), 'UNIQUE') !== false) {
            return null;
        }
        throw $e;
    }
}
