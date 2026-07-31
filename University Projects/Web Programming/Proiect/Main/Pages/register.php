<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

if (is_logged_in()) {
    header('Location: dashboard.php');
    exit;
}

$errors = [];
$successMessage = '';
$formData = [
    'username' => '',
    'full_name' => '',
];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username'] ?? '');
    $fullName = trim($_POST['full_name'] ?? '');
    $password = (string) ($_POST['password'] ?? '');
    $passwordConfirm = (string) ($_POST['password_confirm'] ?? '');

    $formData['username'] = $username;
    $formData['full_name'] = $fullName;

    if ($username === '') {
        $errors[] = 'Nume de utilizator este obligatoriu.';
    } elseif (strlen($username) < 3) {
        $errors[] = 'Nume de utilizator trebuie să aibă cel puțin 3 caractere.';
    }

    if ($fullName === '') {
        $errors[] = 'Nume complet este obligatoriu.';
    }

    if ($password === '') {
        $errors[] = 'Parolă este obligatorie.';
    } elseif (strlen($password) < 6) {
        $errors[] = 'Parolă trebuie să aibă cel puțin 6 caractere.';
    }

    if ($password !== $passwordConfirm) {
        $errors[] = 'Parolele nu se potrivesc.';
    }

    if (!$errors) {
        $passwordHash = password_hash($password, PASSWORD_DEFAULT);
        $newUser = register_user($username, $fullName, $passwordHash);

        if ($newUser === null) {
            $errors[] = 'Nume de utilizator deja existent.';
        } else {
            $successMessage = 'Cont creat cu succes! Poți te conecta acum.';
            $formData = ['username' => '', 'full_name' => ''];
        }
    }
}

?><!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Înregistrare - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../Styles/custom.css">
</head>
<body>
    <main style="max-width: 520px; margin: 48px auto; padding: 24px;">
        <h1>Înregistrare</h1>
        <p>Creează un cont nou pentru a accesa funcțiile aplicației.</p>
        <p><a href="login.php">Ai deja cont? Conectează-te!</a></p>

        <?php if ($errors): ?>
            <div style="color: #b00020;">
                <?php foreach ($errors as $error): ?>
                    <p><?php echo htmlspecialchars($error, ENT_QUOTES, 'UTF-8'); ?></p>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>

        <?php if ($successMessage !== ''): ?>
            <p style="color: #0f6b2f; font-weight: bold;"><?php echo htmlspecialchars($successMessage, ENT_QUOTES, 'UTF-8'); ?></p>
        <?php endif; ?>

        <form method="post" action="register.php">
            <div class="form-group">
                <label for="username">Nume utilizator</label>
                <input id="username" name="username" type="text" value="<?php echo htmlspecialchars((string) $formData['username'], ENT_QUOTES, 'UTF-8'); ?>" required>
            </div>

            <div class="form-group">
                <label for="full_name">Nume complet</label>
                <input id="full_name" name="full_name" type="text" value="<?php echo htmlspecialchars((string) $formData['full_name'], ENT_QUOTES, 'UTF-8'); ?>" required>
            </div>

            <div class="form-group">
                <label for="password">Parolă</label>
                <input id="password" name="password" type="password" required>
            </div>

            <div class="form-group">
                <label for="password_confirm">Confirmare parolă</label>
                <input id="password_confirm" name="password_confirm" type="password" required>
            </div>

            <button type="submit" class="btn btn-primary">Creează cont</button>
        </form>
    </main>
</body>
</html>
