<?php

    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    $login = $_POST['login'];
    $password = md5($_POST['password']);

    $check_user = mysqli_query($connect, "SELECT * FROM `users` WHERE `login` = '$login' AND `password` = '$password'");
    if (mysqli_num_rows($check_user) > 0) {

        $user = mysqli_fetch_assoc($check_user);

        $_SESSION['user'] = [
            "id" => $user['id'],
            "login" => $user['login'],
            "full_name" => $user['full_name'],
            "avatar" => $user['avatar'],
            "email" => $user['email'],
            "role" => $user['role']
        ];
        header('Location: ../index.php');
    }
    else {
        $_SESSION['message'] = 'Неверный логин или пароль';
        header('Location: ../auth.php');
    }
    
