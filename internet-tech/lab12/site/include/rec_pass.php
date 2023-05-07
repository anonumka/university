<?php
    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    // Переменная для хранения символов 
    $chars = 'abdefhiknrstyzABDEFGHKNQRSTYZ23456789';
    // Получаем длину строки
    $numChars = strlen($chars);
    // Переменная для пароля
    $pass = '';
    // Цикл для создания пароля
    for ($i = 0; $i < 8; $i++  ) {
        $pass .= substr($chars, rand(1, $numChars) - 1, 1);
    }

    $email = $_POST['email'];
    
    // Переменная $headers нужна для Email заголовка
    $headers  = "MIME-Version: 1.0\r\n";
    $headers .= "Content-type: text/html; charset=utf-8\r\n";
    $headers .= "To: <$email>\r\n";
    $headers .= "From: <admin@mygram.ru>\r\n";
    // Сообщение для Email
    $message = '
            <html>
            <head>
            <title>Восстановление пароля</title>
            </head>
            <body>
            <p>Ваш новый пароль: ' . $pass . '</p>
            </body>
            </html>
            ';
    
    // Меняем хеш в БД
    $pass = md5($pass);
    mysqli_query($connect, "UPDATE `users` SET `password` = '$pass' WHERE `email` = '$email'");
    // проверка отправилась ли почта
    if (mail($email, "Восстановление пароля через Email", $message, $headers)) {
        // Если да, то выводит сообщение
        $_SESSION['message'] = 'Ссылка для восстановления пароля отправленная на вашу почту';
        header('Location: ../forgot_password.php');
    } else {
        $_SESSION['message'] = 'Произошла какая-то ошибка, письмо отправилось';
        header('Location: ../forgot_password.php');
    }
?>