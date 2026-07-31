<?php

declare(strict_types=1);

const APP_NAME = 'Service Auto';

const APP_BASE_PATH = __DIR__ . '/..';
const APP_UPLOAD_DIR = APP_BASE_PATH . '/uploads';

const DB_DRIVER = 'mysql';
const DB_HOST = '127.0.0.1';
const DB_PORT = '3306';
const DB_NAME = 'service_auto';
const DB_USER = 'root';
const DB_PASS = '';

const SQLITE_PATH = APP_BASE_PATH . '/storage/auxiliary.sqlite';

const REMEMBER_ME_COOKIE = 'service_auto_remember';
const REMEMBER_ME_DAYS = 30;
