function v = flip_stats(nflip, nexp)
    v = zeros(nflip +1, 1);
    for i = 1:nexp
       r = coin_flip(nflip);
       h = sum_tails(r);
       v(h+1) = v(h+1) + 1;
    endfor
endfunction