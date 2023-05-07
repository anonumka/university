<?php
    session_start();
    require_once 'connect.php';

    error_reporting(-1);
    ini_set('display_errors', 'On');

    $xml = simplexml_load_file($_FILES['xml_file']['tmp_name']);
    echo $xml;

    foreach ($xml->children() as $row) {
        $full_name = $row->full_name;
        $role = $row->role;
        $login = $row->login;
        $email = $row->email;
        $password = md5($row->password);
        mysqli_query($connect, "INSERT INTO `users` (`id`, `full_name`, `role`, `login`, `email`, `password`, `avatar`) VALUES (NULL, '$full_name', '$role', '$login', '$email', '$password', NULL)");         
    }

    
    $_SESSION['message'] = 'Добавление прошло успешно';
    header('Location: ../admin.php');
?>