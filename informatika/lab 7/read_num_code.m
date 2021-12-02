% Заготовка функции считывания машинного кода из строки для студентов
% Для примера в качестве "кода" используется простая двоичная запись
% Автор: Кирилл Владимирович Пушкарёв
% Версия: 20201128
% Параметры:
% s - строка, содержащая запись числа в коде
function n = read_num_code(s)
    negative_number = false;
    if s(1) == '1'
      negative_number = true;
      max_num = 2^(length(s) - 1);
      s(1) = '0';
    endif
    n = bin2dec(s);
    if negative_number
      n -= max_num;
    endif
end
