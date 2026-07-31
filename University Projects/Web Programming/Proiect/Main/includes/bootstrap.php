<?php

declare(strict_types=1);

require_once __DIR__ . '/../config/app.php';
require_once __DIR__ . '/db.php';
require_once __DIR__ . '/auth.php';

if (session_status() !== PHP_SESSION_ACTIVE) {
    session_name('service_auto_session');
    session_start();
}

auto_login_from_remember_cookie();
