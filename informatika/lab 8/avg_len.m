function len = avg_len (code, prob)
    len = 0; % Обнуляем len
    len_alph = length(prob);
    for c = 1:len_alph                          % ср. длина составляется из длины кодового слова
        len = len + length(code{c}) * prob(c);  % умноженное на вероятность кода
    endfor
endfunction
