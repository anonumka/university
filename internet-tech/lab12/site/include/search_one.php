<?php
    session_start();
    require_once 'connect.php';

    $search_text = $_GET['search_text'];
    $search_type = $_GET['search_type'];

    error_reporting(-1);
    ini_set('display_errors', 'On');

    if ($search_type === 'user')
    {
        $check_user = mysqli_query($connect, "SELECT * FROM `users` WHERE `login` = '$search_text'");

        if (mysqli_num_rows($check_user) > 0) {
            header('Location: ../user.php?username=' . $search_text);
        }
        else {
            $_SESSION['message'] = 'Пользователь '. $search_text . ' не найден';
            header('Location: ../search.php');
        }
    }
    else
    {
        $check_user = mysqli_query($connect, "SELECT * FROM `posts` WHERE `name` LIKE '%$search_text%' OR `descr` LIKE '%$search_text%'");

        if (mysqli_num_rows($check_user) > 0) {
            $_SESSION['message'] = 'FIND';
            header('Location: ../search.php?value=' . $search_text);
        }
        else {
            $_SESSION['message'] = 'Посты по запросу "'. $search_text . '" не найдены';
            header('Location: ../search.php');
        }
    }


