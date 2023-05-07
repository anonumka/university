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
		<form action="include/signup.php" method="post" enctype="multipart/form-data">
			<label>Фамилия и имя</label>
			<input type="text" name="full_name" placeholder="Введите фамилию и имя">
			<label>Логин</label>
			<input type="text" name="login" placeholder="Введите логин">
			<label>Почта</label>
			<input type="email" name="email" placeholder="Введите свою электронную почту">
			<label>Изображение профиля</label>
			<input type="file" name="avatar">
			<label>Пароль</label>
			<input type="password" name="password" placeholder="Введите пароль">
			<label>Подтверждение пароля</label>
			<input type="password" name="password_confirm" placeholder="Подтвердите пароль">
			<button type="submit">Зарегистрироваться</button>
			<p>
				<a href="/auth.php">Авторизация</a>
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
