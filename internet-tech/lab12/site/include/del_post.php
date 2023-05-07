<?php
    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');
    
    $photo_id = $_GET['photo_id'];

    mysqli_query($connect, "DELETE FROM `posts` WHERE `id_photos` = '$photo_id'");

    $_SESSION['message'] = 'Пост успешно удален';
    header('Location: ../profile.php');
    
?>