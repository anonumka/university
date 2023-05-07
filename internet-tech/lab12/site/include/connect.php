<?php

    $connect = mysqli_connect('localhost', 'root', '', 'lab12');

    if (!$connect) {
        die('Error connect to Database');
    }