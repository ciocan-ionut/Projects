<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

require_login();
require_role(['admin', 'technician', 'client']);

$pdo = db_pdo();
$currentUser = current_user();
$ticketId = filter_input(INPUT_GET, 'id', FILTER_VALIDATE_INT) ?: filter_input(INPUT_POST, 'id', FILTER_VALIDATE_INT);
$editing = $ticketId !== null && $ticketId !== false;

$ticket = [
    'numar_inmatriculare' => '',
    'marca' => '',
    'model' => '',
    'problema' => '',
    'file_path' => null,
];

if ($editing) {
    $stmt = $pdo->prepare('SELECT * FROM tickets WHERE id = :id LIMIT 1');
    $stmt->execute(['id' => $ticketId]);
    $existing = $stmt->fetch();

    if (!$existing) {
        http_response_code(404);
        echo 'Ticket inexistent.';
        exit;
    }

    if ($currentUser['role'] === 'client' && (int) $existing['user_id'] !== (int) $currentUser['id']) {
        http_response_code(403);
        echo 'Nu poți modifica acest ticket.';
        exit;
    }

    $ticket = $existing;
}

$brands = [
    'Dacia' => ['Logan', 'Duster', 'Sandero', 'Spring'],
    'Renault' => ['Clio', 'Megane', 'Captur', 'Kadjar'],
    'Ford' => ['Focus', 'Fiesta', 'Puma', 'Kuga'],
];

$errors = [];
$successMessage = isset($_GET['status']) && $_GET['status'] === 'file_deleted' ? 'Fișierul a fost șters.' : '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['delete_file']) && $editing && !empty($ticket['file_path'])) {
        $fileAbsolutePath = APP_BASE_PATH . '/' . ltrim((string) $ticket['file_path'], '/');
        if (is_file($fileAbsolutePath)) {
            unlink($fileAbsolutePath);
        }

        $stmt = $pdo->prepare('UPDATE tickets SET file_path = NULL WHERE id = :id');
        $stmt->execute(['id' => $ticketId]);

        header('Location: ticket-form.php?id=' . (int) $ticketId . '&status=file_deleted');
        exit;
    }

    $ticket['numar_inmatriculare'] = trim($_POST['numar_inmatriculare'] ?? '');
    $ticket['marca'] = trim($_POST['marca'] ?? '');
    $ticket['model'] = trim($_POST['model'] ?? '');
    $ticket['problema'] = trim($_POST['problema'] ?? '');
    $replaceFile = false;

    if ($ticket['numar_inmatriculare'] === '') {
        $errors[] = 'Numărul de înmatriculare este obligatoriu.';
    }

    if ($ticket['marca'] === '' || !array_key_exists($ticket['marca'], $brands)) {
        $errors[] = 'Selectează o marcă validă.';
    }

    if ($ticket['model'] === '' || !in_array($ticket['model'], $brands[$ticket['marca']] ?? [], true)) {
        $errors[] = 'Selectează un model valid.';
    }

    if ($ticket['problema'] === '') {
        $errors[] = 'Descrierea problemei este obligatorie.';
    }

    if (isset($_FILES['poza_daune']) && $_FILES['poza_daune']['error'] === UPLOAD_ERR_OK) {
        $allowedExtensions = ['jpg', 'jpeg', 'png', 'webp'];
        $extension = strtolower(pathinfo($_FILES['poza_daune']['name'], PATHINFO_EXTENSION));
        $fileSize = (int) $_FILES['poza_daune']['size'];

        if (!in_array($extension, $allowedExtensions, true)) {
            $errors[] = 'Fișierul trebuie să fie JPG, PNG sau WEBP.';
        }

        if ($fileSize > 3 * 1024 * 1024) {
            $errors[] = 'Dimensiunea maximă permisă este 3 MB.';
        }

        if (!$errors) {
            $uploadDir = APP_UPLOAD_DIR . '/tickets';
            if (!is_dir($uploadDir)) {
                mkdir($uploadDir, 0775, true);
            }

            $newFileName = bin2hex(random_bytes(16)) . '.' . $extension;
            $destination = $uploadDir . '/' . $newFileName;

            if (move_uploaded_file($_FILES['poza_daune']['tmp_name'], $destination)) {
                if ($editing && !empty($ticket['file_path'])) {
                    $oldFilePath = APP_BASE_PATH . '/' . ltrim((string) $ticket['file_path'], '/');
                    if (is_file($oldFilePath)) {
                        unlink($oldFilePath);
                    }
                }

                $ticket['file_path'] = 'Main/uploads/tickets/' . $newFileName;
                $replaceFile = true;
            } else {
                $errors[] = 'Fișierul nu a putut fi încărcat.';
            }
        }
    }

    if (!$errors && $successMessage === '') {
        if ($editing) {
            $stmt = $pdo->prepare('UPDATE tickets SET numar_inmatriculare = :numar_inmatriculare, marca = :marca, model = :model, problema = :problema, file_path = :file_path WHERE id = :id');
            $stmt->execute([
                'numar_inmatriculare' => $ticket['numar_inmatriculare'],
                'marca' => $ticket['marca'],
                'model' => $ticket['model'],
                'problema' => $ticket['problema'],
                'file_path' => $ticket['file_path'],
                'id' => $ticketId,
            ]);
            $successMessage = 'Ticket-ul a fost actualizat.';
        } else {
            $stmt = $pdo->prepare('INSERT INTO tickets (user_id, numar_inmatriculare, marca, model, problema, file_path) VALUES (:user_id, :numar_inmatriculare, :marca, :model, :problema, :file_path)');
            $stmt->execute([
                'user_id' => (int) $currentUser['id'],
                'numar_inmatriculare' => $ticket['numar_inmatriculare'],
                'marca' => $ticket['marca'],
                'model' => $ticket['model'],
                'problema' => $ticket['problema'],
                'file_path' => $ticket['file_path'],
            ]);
            $successMessage = 'Ticket-ul a fost salvat.';

            $ticketId = (int) $pdo->lastInsertId();
            $editing = true;
        }

        if ($replaceFile) {
            $successMessage = $editing ? 'Ticket-ul a fost actualizat cu fișier nou.' : 'Ticket-ul a fost salvat cu fișier nou.';
        }
    }
}

?><!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $editing ? 'Editează ticket' : 'Creează ticket'; ?> - <?php echo APP_NAME; ?></title>
    <link rel="stylesheet" href="../Styles/custom.css">
</head>
<body>
    <main style="max-width: 760px; margin: 40px auto; padding: 24px;">
        <h1><?php echo $editing ? 'Editează ticket' : 'Creează ticket'; ?></h1>
        <p><a href="dashboard.php">Înapoi la dashboard</a></p>

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

        <form method="post" enctype="multipart/form-data" action="ticket-form.php<?php echo $editing ? '?id=' . (int) $ticketId : ''; ?>">
            <input type="hidden" name="id" value="<?php echo $editing ? (int) $ticketId : ''; ?>">

            <div class="form-group">
                <label for="numar_inmatriculare">Număr Înmatriculare</label>
                <input id="numar_inmatriculare" name="numar_inmatriculare" type="text" value="<?php echo htmlspecialchars((string) $ticket['numar_inmatriculare'], ENT_QUOTES, 'UTF-8'); ?>" required>
            </div>

            <div class="form-group">
                <label for="marca-select">Marcă</label>
                <select id="marca-select" name="marca" required>
                    <option value="">Alege marca</option>
                    <?php foreach ($brands as $brand => $models): ?>
                        <option value="<?php echo htmlspecialchars($brand, ENT_QUOTES, 'UTF-8'); ?>" <?php echo $ticket['marca'] === $brand ? 'selected' : ''; ?>><?php echo htmlspecialchars($brand, ENT_QUOTES, 'UTF-8'); ?></option>
                    <?php endforeach; ?>
                </select>
            </div>

            <div class="form-group">
                <label for="model-select">Model</label>
                <select id="model-select" name="model" <?php echo $ticket['marca'] === '' ? 'disabled' : ''; ?> required>
                    <option value="">Alege modelul</option>
                    <?php if ($ticket['marca'] !== '' && isset($brands[$ticket['marca']])): ?>
                        <?php foreach ($brands[$ticket['marca']] as $model): ?>
                            <option value="<?php echo htmlspecialchars($model, ENT_QUOTES, 'UTF-8'); ?>" <?php echo $ticket['model'] === $model ? 'selected' : ''; ?>><?php echo htmlspecialchars($model, ENT_QUOTES, 'UTF-8'); ?></option>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </select>
            </div>

            <div class="form-group">
                <label for="poza_daune">Încarcă poză daune</label>
                <input id="poza_daune" name="poza_daune" type="file" accept="image/png,image/jpeg,image/webp">
                <?php if ($editing && !empty($ticket['file_path'])): ?>
                    <p>Fișier curent: <?php echo htmlspecialchars((string) $ticket['file_path'], ENT_QUOTES, 'UTF-8'); ?></p>
                    <button type="submit" name="delete_file" value="1" class="btn btn-secondary">Șterge fișierul</button>
                <?php endif; ?>
            </div>

            <div class="form-group">
                <label for="problema">Problemă reclamată</label>
                <textarea id="problema" name="problema" rows="5" required><?php echo htmlspecialchars((string) $ticket['problema'], ENT_QUOTES, 'UTF-8'); ?></textarea>
            </div>

            <button type="submit" class="btn btn-primary"><?php echo $editing ? 'Actualizează ticket' : 'Salvează ticket'; ?></button>
        </form>
    </main>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
    <script src="../Scripts/data.js"></script>
    <script src="../Scripts/mainJQuery.js"></script>
    <script>
        $(function () {
            const $marcaSelect = $('#marca-select');
            if ($marcaSelect.length && $marcaSelect.val()) {
                $marcaSelect.trigger('change');
            }
        });
    </script>
</body>
</html>
