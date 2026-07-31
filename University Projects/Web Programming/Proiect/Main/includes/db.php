<?php

declare(strict_types=1);

function db_pdo(): PDO
{
    static $pdo = null;

    if ($pdo instanceof PDO) {
        return $pdo;
    }

    if (DB_DRIVER === 'sqlite') {
        $pdo = new PDO('sqlite:' . SQLITE_PATH);
    } else {
        $dsn = sprintf('mysql:host=%s;port=%s;dbname=%s;charset=utf8mb4', DB_HOST, DB_PORT, DB_NAME);
        $pdo = new PDO($dsn, DB_USER, DB_PASS, [
            PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_EMULATE_PREPARES => false,
        ]);
    }

    return $pdo;
}

function db_mysqli(): mysqli
{
    static $mysqli = null;

    if ($mysqli instanceof mysqli) {
        return $mysqli;
    }

    $mysqli = mysqli_init();
    $mysqli->real_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME, (int) DB_PORT);
    $mysqli->set_charset('utf8mb4');

    return $mysqli;
}
