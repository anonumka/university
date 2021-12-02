% Заготовка функции считывания двоичного числа из строки для студентов.
% Функция не умеет обрабатывать отрицательные и дробные числа!
% Автор: Кирилл Владимирович Пушкарёв
% Версия: 20201116
% Параметры:
% s - строка, содержащая запись числа в двоичной системе счисления.
% Результаты:
% n - число, считанное из строки s.
function n = read_num_bin(s)
    % Инициализируем n нулём
    n = 0;
    negative_number = false;
    main_s = '';
    last_s = '';
    % Перебираем в цикле символы строки s
    if s(1) == '-'
      negative_number = true;
      s(1) = [];
    endif
    for c = s
      if (c == '.')
        break;
      endif
      n = n * 2 + str2num(c);
      % Сдвигаем результат на один разряд влево и добавляем следующую цифру
      main_s = [main_s c];
    end
    len = length(main_s);
    pow = 1;
    for c = s((len+2):end)
      last_s = [last_s c];
      n = n + str2num(c) * 2^(-pow);
      pow++;
    endfor
    if negative_number
      n = -n;
    endif
end
