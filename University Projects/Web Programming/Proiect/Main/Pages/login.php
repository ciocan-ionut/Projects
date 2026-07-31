<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

$error = '';
$username = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username'] ?? '');
    $password = (string) ($_POST['password'] ?? '');
    $rememberMe = isset($_POST['remember_me']);

    $user = authenticate_user($username, $password);

    if ($user) {
        login_user($user);
        if ($rememberMe) {
            remember_user((int) $user['id']);
        }
        header('Location: dashboard.php');
        exit;
    }

    $error = 'Nume de utilizator sau parolă invalidă.';
}

?><!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Autentificare - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../Styles/custom.css">
</head>
<body>
    <main style="max-width: 520px; margin: 48px auto; padding: 24px;">
        <h1>Autentificare</h1>
        <p>Conectează-te pentru a accesa funcțiile protejate.</p>
        <p><a href="register.php">Nu ai cont? Înregistrează-te!</a></p>

        <?php if ($error !== ''): ?>
            <p style="color: #b00020; font-weight: bold;"><?php echo htmlspecialchars($error, ENT_QUOTES, 'UTF-8'); ?></p>
        <?php endif; ?>

        <form method="post" action="login.php">
            <div class="form-group">
                <label for="username">Nume utilizator</label>
                <input id="username" name="username" type="text" value="<?php echo htmlspecialchars($username, ENT_QUOTES, 'UTF-8'); ?>" required>
            </div>

            <div class="form-group">
                <label for="password">Parolă</label>
                <input id="password" name="password" type="password" required>
            </div>

            <div class="form-group">
                <label>
                    <input type="checkbox" name="remember_me" value="1">
                    Remember me
                </label>
            </div>

            <button type="submit" class="btn btn-primary">Intră în cont</button>
        </form>
    </main>
</body>
</html>
