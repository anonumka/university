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
	<div id="output_information">
		<?php include 'include/profile_user.php';
		while ( $res = mysqli_fetch_assoc( $all_posts ) )
		{
			echo '<div class="post"><img src="' . $res['photo'] . '">';

			echo '<span class="title">';
			echo $res['name']; echo '</span>';

			echo '<span class="description">';
			echo $res['descr']; echo '</span>';

			echo '<span class="author">Автор: <a href="user.php?username=' . $res['author'] . '">';
			echo $res['author']; echo '</a></span></div>';
		}
		?>
	</div>
	<?php include 'template/footer.php'; ?>
</body>
</html>
