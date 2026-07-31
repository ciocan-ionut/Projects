<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

require_login();
require_role(['admin', 'technician']);

$mysqli = db_mysqli();
$result = $mysqli->query('SELECT id, numar_inmatriculare, marca, model, problema, file_path, created_at FROM tickets ORDER BY created_at DESC');

?><!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Management - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../Styles/custom.css">
</head>
<body>
    <main style="max-width: 1100px; margin: 40px auto; padding: 24px;">
        <h1>Management tickete</h1>
        <p><a href="dashboard.php">Înapoi la dashboard</a> | <a href="ticket-form.php">Ticket nou</a></p>

        <table style="width: 100%; border-collapse: collapse;">
            <thead>
                <tr>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">ID</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Număr</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Marcă</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Model</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Problemă</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Fișier</th>
                    <th style="text-align: left; border-bottom: 1px solid #ccc; padding: 8px;">Acțiuni</th>
                </tr>
            </thead>
            <tbody>
                <?php while ($row = $result->fetch_assoc()): ?>
                    <tr>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo (int) $row['id']; ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo htmlspecialchars($row['numar_inmatriculare'], ENT_QUOTES, 'UTF-8'); ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo htmlspecialchars($row['marca'], ENT_QUOTES, 'UTF-8'); ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo htmlspecialchars($row['model'], ENT_QUOTES, 'UTF-8'); ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo htmlspecialchars($row['problema'], ENT_QUOTES, 'UTF-8'); ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><?php echo $row['file_path'] ? htmlspecialchars($row['file_path'], ENT_QUOTES, 'UTF-8') : '-'; ?></td>
                        <td style="padding: 8px; border-bottom: 1px solid #eee;"><a href="ticket-form.php?id=<?php echo (int) $row['id']; ?>">Editează</a></td>
                    </tr>
                <?php endwhile; ?>
            </tbody>
        </table>
    </main>
</body>
</html>
