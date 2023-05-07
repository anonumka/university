  
    <header class="header">
            <div>
                <a class="nav_link" href="/"><img src="template/images/logo.png"></a>
            </div>
            <nav id="nav_header">
                
                <a class="nav_link" href="/create_post.php"><img src="template/images/plus.png"></a>
                <?php 
                    if ($_SESSION['user']['role'] == 2) {
                        echo "<a class='nav_link' href='/admin.php'>Админ панель</a>";
                    }
                ?>
                <a class="nav_link" href="profile.php"><img src="template/images/profile.png"></a>
                <a class="nav_link" href="search.php"><img src="template/images/search.png"></a>
                <a class="nav_link" href="include/logout.php"><img src="template/images/logout.png"></a>
            </nav>
    </header>