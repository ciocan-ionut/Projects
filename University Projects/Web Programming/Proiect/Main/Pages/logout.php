<?php

declare(strict_types=1);

require_once __DIR__ . '/../includes/bootstrap.php';

logout_user();

clear_remember_cookie();

header('Location: login.php');
exit;

