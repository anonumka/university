<?php
	session_start();

	if (!$_SESSION['user']) {
        header('Location: ../auth.php');
    }
?>
<html>
<head>
	<title>МойГрам</title>
	<link href="style.css" rel="stylesheet">
	<link href="style_template.css" rel="stylesheet">
</head>
<body>
	<?php include 'template/header.php'; ?>
    <form action="include/load_xml.php" method="post" enctype="multipart/form-data">
        <label>Приложите xml-файл пользователей</label>
        <input type="file" name="xml_file">
        <button type="submit">Отправить</button>
        <?php
            if ($_SESSION['message']) {
                echo '<p class="msg">' . $_SESSION['message'] . '</p>';
            }
            unset($_SESSION['message']);
        ?> 
    </form>
    <?php include 'template/footer.php'; ?>
</body>