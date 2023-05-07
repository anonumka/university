<?php
	session_start();

	if ($_SESSION['user']) {
        header('Location: ../index.php');
    }
?>

<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>МойГрам</title>
    <link href="style_form.css" rel="stylesheet">
</head>
<body>
    <div class="auth__form">
        <form action="include/rec_pass.php" method="post">
            <label>Введите ваш EMail: </label>
            <input type="email" name="email">
            <input type="submit" value="Отправить" name="doGo">
            <p>
				<a href="/auth.php">Авторизоваться</a>
			</p>
            <?php
                if ($_SESSION['message']) {
                    echo '<p class="msg">' . $_SESSION['message'] . '</p>';
                }
                unset($_SESSION['message']);
            ?> 
        </form>
    </div>
</body>
</html>