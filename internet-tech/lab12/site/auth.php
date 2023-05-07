<?php
	session_start();

	if ($_SESSION['user']) {
        header('Location: ../profile.php');
    }
?>

<html>
<head>
	<title>МойГрам</title>
	<metacharset=”utf-8”>
	<link href="style_form.css" rel="stylesheet">
</head>
<body>
	<div class="auth__form">
		<form action="include/signin.php" method="post">
			<label>Логин</label>
			<input type="text" name="login" placeholder="Введите логин">
			<label>Пароль</label>
			<input type="password" name="password" placeholder="Введите пароль">
			<button type="submit">Войти</button>
			<p>
				<a href="/register.php">Регистрация</a>
			</p>
			<p>
				<a href="/forgot_password.php">Восстановление пароля</a>
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
