% Заготовка функции кодирования сообщения для студентов
% Автор: Кирилл Владимирович Пушкарёв
% Дата: 5 декабря 2019 г.
% Версия: 0.1
% Параметры:
% msg - строка сообщения из символов алфавита Hex, состоящего из 16-ричных цифр 0, ..., 9, A, ..., F
% code - ячейковый массив кодовых слов (code{i} — кодовое слово для i-й буквы первичного алфавита)
function emsg = encode_msg(msg, code)
    len_msg = numel(msg);
    % Формируем вектор символов алфавита
    alph = ['0':'9' 'A':'F'];
    % Инициализируем строку результата
    emsg = '';
    % Просматриваем сообщение посимвольно
    for c = 1:len_msg
        % Находим символ c в алфавите и подставляем соответствующий код
        search_char = find(alph == msg(c));
        emsg = [emsg code{search_char}];
    end
end
