<?php
    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');
    
    $name = $_POST['name'];
    $descr = $_POST['descr'];
    $author = $_SESSION['user']['login'];

    $path = 'uploads/users_photos/' . time() . $_FILES['photo']['name'];

    if (!move_uploaded_file($_FILES['photo']['tmp_name'], '../' . $path)) {
        $_SESSION['message'] = 'Ошибка при загрузке фотографии';
        header('Location: ../create_post.php');
    }
    else {
        mysqli_query($connect, "INSERT INTO `posts` (`id_photos`, `name`, `descr`, `photo`, `author`) VALUES (NULL, '$name', '$descr', '$path', '$author')");

        $_SESSION['message'] = 'Пост добавлен успешно';
        header('Location: ../index.php');
    }
    
?>