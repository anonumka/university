<?php

    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    $username = $_GET['username'];

    $all_posts = mysqli_query($connect, "SELECT * FROM `posts` WHERE `author` = '$username'");

?>
