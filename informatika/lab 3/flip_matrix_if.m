function [r] = flip_matrix_if(r)
    check = (r(:,end) < 0.5);
    r(check,:) = fliplr(r(check,:));
endfunction