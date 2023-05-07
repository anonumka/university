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
	<?php
		if ($_SESSION['message']) {
			echo '<p class="msg">' . $_SESSION['message'] . '</p>';
		}
		unset($_SESSION['message']);
	?> 
	<div id="output_information">
		<?php include 'include/all_posts.php';


		$count = mysqli_num_rows($all_posts) / 3;
		$cur_page = $_GET['page'];

		if (!$cur_page) {
			$all_posts = mysqli_query($connect, "SELECT * FROM `posts` LIMIT 3");
		}
		else {
			$cur_page = $cur_page * 3;
			$next_page = $cur_page + 3;
			$all_posts = mysqli_query($connect, "SELECT * FROM `posts` LIMIT $cur_page, $next_page");
		}

		while ( $res = mysqli_fetch_assoc( $all_posts ) )
		{
			echo '<div class="post"><a href="' . $res['photo'] . '"><img src="template/watermark.php?image=' . $res['photo'] . '"></a>';

			echo '<span class="title">';
			echo $res['name']; echo '</span>';

			echo '<span class="description">';
			echo $res['descr']; echo '</span>';

			echo '<span class="author">Автор: <a href="user.php?username=' . $res['author'] . '">';
			echo $res['author']; echo '</a></span></div>';
		}
		?>
	</div>
	<div id="pages">
		<?php
			for ($i=0; $i < $count; $i++)
			{
				echo '<a href="index.php?page=' . $i . '">' . $i+1 . '</a>';
			}
		?>
	</div>
	<?php include 'template/footer.php'; ?>
</body>
</html>
