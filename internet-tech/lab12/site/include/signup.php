<?php
    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');
    
    $full_name = $_POST['full_name'];
    $login = $_POST['login'];
    $email = $_POST['email'];
    $password = $_POST['password'];
    $password_confirm = $_POST['password_confirm'];

    if ($password != $password_confirm) {
        $_SESSION['message'] = 'Пароли не совпадают';
        header('Location: ../register.php');
    }
    else {
        $path = 'uploads/users_avatars/' . time() . $_FILES['avatar']['name'];

        if (!move_uploaded_file($_FILES['avatar']['tmp_name'], '../' . $path)) {
            $_SESSION['message'] = 'Ошибка при загрузке аватара';
            header('Location: ../register.php');
        }
        else {
            $password = md5($password);


            $ans = mysqli_query($connect, "SELECT * FROM `users` WHERE `login` = '$login'");

            if (mysqli_num_rows($ans) > 0) 
            {
                $_SESSION['message'] = 'Данный логин уже занят';
                header('Location: ../register.php');
            }
            else
            {
                $ans = mysqli_query($connect, "SELECT * FROM `users` WHERE `email` = '$email'");

                if (mysqli_num_rows($ans) > 0)
                {
                    $_SESSION['message'] = 'Данный email занят';
                    header('Location: ../register.php');
                }
                else
                {
                    mysqli_query($connect, "INSERT INTO `users` (`id`, `full_name`, `role`, `login`, `email`, `password`, `avatar`) VALUES (NULL, '$full_name', 0, '$login', '$email', '$password', '$path')");

                    $_SESSION['message'] = 'Регистрация прошла успешно';
                    header('Location: ../auth.php');
                }
            }
        }
    }
    
?>