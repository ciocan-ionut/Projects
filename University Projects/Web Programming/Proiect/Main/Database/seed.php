<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

$pdo = db_pdo();
$pdo->beginTransaction();

$pdo->exec('DELETE FROM remember_tokens');
$pdo->exec('DELETE FROM tickets');
$pdo->exec('DELETE FROM users');
$pdo->exec('DELETE FROM roles');

$roles = ['admin', 'technician', 'client'];
$roleIds = [];

$roleStmt = $pdo->prepare('INSERT INTO roles (name) VALUES (:name)');
foreach ($roles as $role) {
    $roleStmt->execute(['name' => $role]);
    $roleIds[$role] = (int) $pdo->lastInsertId();
}

$userStmt = $pdo->prepare('INSERT INTO users (role_id, username, password_hash, full_name) VALUES (:role_id, :username, :password_hash, :full_name)');

$userStmt->execute([
    'role_id' => $roleIds['admin'],
    'username' => 'admin',
    'password_hash' => password_hash('admin123', PASSWORD_DEFAULT),
    'full_name' => 'Administrator Service',
]);
$adminId = (int) $pdo->lastInsertId();

$userStmt->execute([
    'role_id' => $roleIds['technician'],
    'username' => 'tech',
    'password_hash' => password_hash('tech123', PASSWORD_DEFAULT),
    'full_name' => 'Tehnician Service',
]);
$technicianId = (int) $pdo->lastInsertId();

$ticketStmt = $pdo->prepare('INSERT INTO tickets (user_id, numar_inmatriculare, marca, model, problema, file_path) VALUES (:user_id, :numar_inmatriculare, :marca, :model, :problema, :file_path)');
$ticketStmt->execute([
    'user_id' => $adminId,
    'numar_inmatriculare' => 'B-123-XYZ',
    'marca' => 'Dacia',
    'model' => 'Logan',
    'problema' => 'Revizie generală',
    'file_path' => null,
]);

$ticketStmt->execute([
    'user_id' => $technicianId,
    'numar_inmatriculare' => 'CJ-99-ABC',
    'marca' => 'Renault',
    'model' => 'Clio',
    'problema' => 'Schimb distribuție',
    'file_path' => null,
]);

$pdo->commit();

echo "Seed completed.\n";
