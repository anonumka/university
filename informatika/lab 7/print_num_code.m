% Заготовка функции представления числа в коде для студентов
% Для примера в качестве "кода" используется простая двоичная запись
% Автор: Кирилл Владимирович Пушкарёв
% Версия: 20201128
% Параметры:
% n - число
% len - разрядность кода
function s = print_num_code(n, len)
    negative_number = false;
    if n < 0
        negative_number = true;
        max_num = 2^(len-1);
        n = max_num + n;
    end
    s = dec2bin(n, len);
    if negative_number
      s(1) = '1';
    endif
end