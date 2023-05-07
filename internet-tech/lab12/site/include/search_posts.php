<?php

    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    $back = $_GET['page'];
    $next = $back + 3;

    $all_posts = mysqli_query($connect, "SELECT * FROM `posts` LIMIT $back, $next");
