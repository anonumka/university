<?php

    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    $all_posts = mysqli_query($connect, "SELECT * FROM `posts`");