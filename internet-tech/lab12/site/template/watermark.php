<?php
    error_reporting(-1);
    ini_set('display_errors', 'On');

    // получаем имя изображения через GET
    $image = '../' . $_GET['image'];
    $im = imagecreatefromjpeg($image);

    // создаём водяной знак
    $stamp = imagecreatefrompng('images/watermark.png');

    // получаем значения высоты и ширины водяного знака
    $marge_right = 10;
    $marge_bottom = 10;
    $sx = imagesx($stamp);
    $sy = imagesy($stamp);

    // создаём jpg из оригинального изображения
    imagecopy($im, $stamp, imagesx($im) - $sx - $marge_right, imagesy($im) - $sy - $marge_bottom, 0, 0, imagesx($stamp), imagesy($stamp));

    // Output and free memory
    header('Content-type: image/png');
    imagepng($im);
    imagedestroy($im);
?>
