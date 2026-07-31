<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

require_login();
require_role(['admin', 'technician']);

$user = current_user();

?><!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Dashboard - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../Styles/dashboard.css">
    <link rel="stylesheet" href="../Styles/custom.css">
</head>
<body>
    <main style="max-width: 960px; margin: 48px auto; padding: 24px;">
        <h1>Dashboard protejat</h1>
        <p>Salut, <?php echo htmlspecialchars($user['full_name'], ENT_QUOTES, 'UTF-8'); ?>. Rol: <?php echo htmlspecialchars($user['role'], ENT_QUOTES, 'UTF-8'); ?>.</p>
        <p><a href="logout.php">Logout</a></p>
        <section>
            <h2>Următorul pas</h2>
            <p><a href="ticket-form.php">Creează un ticket</a>, <a href="management-page.php">vezi managementul</a> sau <a href="ticket-form.php?id=1">deschide un ticket existent</a>.</p>
        </section>
    </main>
</body>
</html>
