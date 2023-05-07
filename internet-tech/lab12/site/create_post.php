<?php
	session_start();
?>

<html>
<head>
	<title>МойГрам</title>
	<link href="style_form.css" rel="stylesheet">
    <link href="style_template.css" rel="stylesheet">
</head>
<body>
    <?php include 'template/header.php' ?>
	<div class="auth__form">
		<form action="include/add_post.php" method="post" enctype="multipart/form-data">
			<label>Название</label>
			<input type="text" name="name" placeholder="Введите название">
			<label>Описание</label>
			<input type="text" name="descr" placeholder="Введите описание">
            <label>Изображение поста</label>
			<input type="file" name="photo">
			<button type="submit">Добавить</button>
			<p>
				<a href="/index.php">Вернуться</a>
			</p>
			<?php
				if ($_SESSION['message']) {
					echo '<p class="msg">' . $_SESSION['message'] . '</p>';
				}
				unset($_SESSION['message']);
			?> 
		</form>
	</div>
    <?php include 'template/footer.php' ?>
</body>
</html>
