% Инициализировать генератор псевдослучайных чисел
rand ("state", 3);
% Генерация случайного вектора вероятностей для алфавита Hex
hex = rand(1, 16);
hex = hex / sum(hex);
save('hex.txt','hex','-ascii');
% Построение оптимального двоичного кода по методу Хаффмана
code = {'11000' '1101' '0010' '1110' '1111' '0011001' '0011000' '011' '11001' '00111' '101' '1000' '010' '1001' '000' '001101'};
dlmwrite('code.txt', char(code), '');
% Генерация сообщениий и проверка исходного и восстановленного
for c = 1:100
    msg = gen_msg(hex, 100);
    msg_back = encode_msg(msg, code);
    msg_back = decode_msg(msg_back, code);
    if msg_back ~= msg
        error('Number not equal nback (%s != %s)', msg_back, msg);
    end
end
% Формирование вектора results и сохранение с ключом '-ascii'.
len_avg = avg_len(code, hex);
len_min = alph_entropy(hex);
min_bit = min_bits(length(hex));
k_opt = len_min/len_avg;
results = [len_avg len_min min_bit k_opt];
save('results.txt', 'results', '-ascii');