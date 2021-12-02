function [b, n] = calc_info(msg, alph, alph_p)
    b = 0;  
    length_alph = numel(alph);
    length_alph_p = numel(alph_p);
    length_msg = numel(msg);
    
    if length_alph ~= length_alph_p
      error('len alph and len alph_p dont equal!\nsize alph is %d, size alph_p is %d', length_alph, length_alph_p);
    endif
    
    for i = 1:length_msg
      search_char = find(alph == msg(i));
      if isempty(search_char)
        warning('%c symbol was found by index %d excluded this alph', msg(i), i);
        length_msg = length_msg - 1;
      else
        res = alph_p(search_char);
        b += -log2(res);
      endif
    endfor
    n = length_msg*log2(length_alph);
endfunction