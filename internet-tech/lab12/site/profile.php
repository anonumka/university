<?php
	session_start();

    if (!$_SESSION['user']) {
        header('Location: ../auth.php');
    }
?>

<html>
<head>
	<title>МойГрам</title>
	<metacharset=”utf-8”>
	<link href="style_profile.css" rel="stylesheet">
	<link href="style_template.css" rel="stylesheet">
</head>
<body>
	<?php include 'template/header.php'; ?>
	<div class="user">
		<div class="main_part">
			<img src="<?= $_SESSION['user']['avatar'] ?>" style="width: 200px;">
			<h2><?= $_SESSION['user']['full_name'] ?></h2>
			<h3>Ваш логин: <?= $_SESSION['user']['login'] ?></h3>
		</div>
		<div id="output_information">
			<?php require_once 'include/connect.php';
			$all_posts = mysqli_query($connect, "SELECT * FROM `posts` WHERE `author` = '" . $_SESSION['user']['login']. "'");
			while ( $res = mysqli_fetch_assoc( $all_posts ) )
			{
				echo '<div class="post"><img class="photo_prof" src="template/watermark.php?image=' . $res['photo'] . '">';

				echo '<span class="title">';
				echo $res['name']; echo '</span>';

				echo '<span class="description">';
				echo $res['descr']; echo '</span>';

				echo '<a class="trash_icon" type="submit" href="include/del_post.php?photo_id=' . $res['id_photos'] .'"><img src="template/images/trash.png"></a></div>';
			}
			?>
		</div>
	</div>
	<?php include 'template/footer.php'; ?>
</body>
</html>
