-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Хост: localhost
-- Время создания: Май 01 2023 г., 05:30
-- Версия сервера: 10.4.28-MariaDB
-- Версия PHP: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `lab12`
--

-- --------------------------------------------------------

--
-- Структура таблицы `posts`
--

CREATE TABLE `posts` (
  `id_photos` int(11) NOT NULL,
  `name` varchar(50) DEFAULT NULL,
  `descr` varchar(500) DEFAULT NULL,
  `photo` varchar(255) DEFAULT NULL,
  `author` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Дамп данных таблицы `posts`
--

INSERT INTO `posts` (`id_photos`, `name`, `descr`, `photo`, `author`) VALUES
(3, 'рррр', 'нннн', 'uploads/users_photos/1681462641tipa-krytie-chinim.jpg', 'vlad_bmw_power'),
(5, '123', '41241', 'uploads/users_photos/1681464845demon-slayer-tanjiro-wallpaper-43.jpg', 'denchik'),
(6, '4124', '1221', 'uploads/users_photos/1681464857змейка фотка.jpg', 'denchik'),
(7, '4124', '112244', 'uploads/users_photos/1681464877cat.jpg', 'denchik');

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `id` int(11) NOT NULL,
  `full_name` varchar(355) DEFAULT NULL,
  `role` int(1) DEFAULT 0,
  `login` varchar(100) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `avatar` varchar(500) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`id`, `full_name`, `role`, `login`, `email`, `password`, `avatar`) VALUES
(1, 'Денчик Бугатти', 2, 'denchik', 'cergeu912@gmail.com', '9af3969c446b81730c1c67597a256944', 'uploads/users_avatars/1681108166cat.jpg'),
(2, 'Владик БМВ', 0, 'vlad_bmw_power', 'vlad123@mail.ru', 'caf1a3dfb505ffed0d024130f58c5cfa', 'uploads/users_avatars/1681108231cat.png'),
(3, 'Гоша Невероятный', 0, 'gosha_genius', 'gosha_genius@mail.ru', '7aa1c13634727268f03923b0bc1adaf9', NULL),
(4, 'Кирилл Понятный', 0, 'kirill_understand', 'kirill_understand@mail.ru', '1258644c593c4dac8b9708df0804a75d', NULL),
(5, 'Захар Неуклюжий', 0, 'zahar_fefefe', 'zahar_fefefe@mail.ru', 'faad56cf7c35621b58b1c96744487c8b', NULL);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `posts`
--
ALTER TABLE `posts`
  ADD PRIMARY KEY (`id_photos`);

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `posts`
--
ALTER TABLE `posts`
  MODIFY `id_photos` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
