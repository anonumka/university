<?php
	session_start();

	if (!$_SESSION['user']) {
        header('Location: ../auth.php');
    }

    require_once 'include/connect.php';
?>
<html>
<head>
	<title>МойГрам</title>
	<link href="style_template.css" rel="stylesheet">
    <link href="style_form.css" rel="stylesheet">
    <link href="style.css" rel="stylesheet">
</head>
<body>
	<?php include 'template/header.php'; ?>
    <div class="auth__form">
        <form action="include/search_one.php" method="get">
            <label>Поле ввода</label>
            <input type="text" name="search_text" placeholder="Введите запрос">
            <select name="search_type">
                <option value="user">Пользователь</option>
                <option value="text_post">Содержимое поста</option>
            </select>
            <button type="submit">Поиск</button>
            <p>
                <a href="/index.php">Вернуться на главную</a>
            </p>
        </form>
    </div>
    <?php
        if ($_SESSION['message'] === "FIND") {
            $search_text = $_GET['value'];
            $check_user = mysqli_query($connect, "SELECT * FROM `posts` WHERE `name` LIKE '%$search_text%' OR `descr` LIKE '%$search_text%'");
            while ( $res = mysqli_fetch_assoc( $check_user ) )
            {
                echo '<div class="post"><a href="' . $res['photo'] . '"><img src="template/watermark.php?image=' . $res['photo'] . '"></a>';

                echo '<span class="title">';
                echo $res['name']; echo '</span>';

                echo '<span class="description">';
                echo $res['descr']; echo '</span>';

                echo '<span class="author">Автор: <a href="user.php?username=' . $res['author'] . '">';
                echo $res['author']; echo '</a></span></div>';
            }
        }
        else if ($_SESSION['message']) {
            echo '<p class="msg">' . $_SESSION['message'] . '</p>';
        }
        unset($_SESSION['message']);
    ?> 
    <?php include 'template/footer.php'; ?>
</body>