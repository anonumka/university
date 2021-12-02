function r = alph_redundancy(P)
    h = alph_entropy(P);
    h_max = log2(numel(P));
    r = 1 - (h/h_max);
endfunction