% Программа тестирования функций print_num_bin(), read_num_bin() для практической
% работы по системам счисления.
% Если тестирование успешно, выводит в командное окно сообщение «OK» и возвращает 0.
% Автор: Кирилл Владимирович Пушкарев
% Версия: 20201116
% Результаты:
% fail_count - количество неуспешных тестов.
function fail_count = test()
    print_tests = {
        0 4 '0.0000'
        1 0 '1'
        -1 0 '-1'
        0.1 3 '0.001'
        -15.15 2 '-1111.01'
        8 0 '1000'
        1.5 4 '1.1000'
        1.75 4 '1.1100'
        1.75 2 '1.11'
        1.75 1 '10.0'
        -1.75 1 '-10.0'
    };
    read_tests = {
        '0' 0
        '0.0000' 0
        '1' 1
        '-1' -1
        '0.001' 0.125
        '-1111.01' -15.25
        '1000' 8
        '10.0' 2
        '1010.1010' 10.625
        '-1010.1010' -10.625
    };

    fail_count = data_driven_test(@test_print, print_tests);
    fail_count = fail_count + data_driven_test(@test_read, read_tests);

    pass_count = size(print_tests, 1) + size(read_tests, 1) - fail_count;
    printf('Passed %d, failed %d.\n', pass_count, fail_count);
    if fail_count == 0
        disp('OK');
    end
end

% Функция запуска одного теста для различных данных.
% Параметры:
% testfun - дескриптор функции, отвечающей за выполнение теста. В качестве
%   параметров принимает строку массива data и возвращает true, если тест успешен.
% data - ячейковый массив данных для тестов. Каждая строка соответствует одному примеру.
% Результаты:
% fail_count - количество неудачных тестов.
function fail_count = data_driven_test(testfun, data)
    fail_count = 0;
    for i = 1:size(data, 1)
        fail_count = fail_count + ~testfun(data{i, :});
    end
end

% Функция проверки результата print_num_bin().
% Параметры:
% n - действительное число.
% prec - количество знаков дробной части результата.
% s - строка, представляющая число n.
% Результаты:
% r - логическое значение true, если тест успешен.
function r = test_print(n, prec, s)
    test_desc = sprintf('print_num_bin(%d, %d) == %s', n, prec, s);
    printf('Running test %s... ', test_desc);
    s2 = print_num_bin(n, prec);
    if isequal(s2, s)
        printf('pass.\n');
        r = true;
    else
        printf('fail (%s ~= %s)!\n', s2, s);
        r = false;
    end
end

% Функция проверки результата read_num_bin().
% Параметры:
% s — строка.
% n — число, считанное из строки s.
% Результаты:
% r - логическое значение true, если тест успешен.
function r = test_read(s, n)
    test_desc = sprintf('read_num_bin(%s) == %d', s, n);
    printf('Running test %s... ', test_desc);
    n2 = read_num_bin(s);
    if n2 == n
        printf('pass.\n');
        r = true;
    else
        printf('fail (%d ~= %d)!\n', n2, n);
        r = false;
    end
end
