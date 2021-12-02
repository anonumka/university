%%
rand ("state", 3);
%%
ralph  = rand(1, 16);
ralph  = ralph  / sum(ralph);
save('ralph.txt','ralph','-ascii');
%%
ralph_entropy = alph_entropy(ralph);
ralph_redundancy = alph_redundancy(ralph);
%%
msg = gen_msg(ralph, 100);
dlmwrite('msg.txt', msg, '');
%%
[b,n] = calc_info(msg, ['0':'9' 'A':'F'], ralph);
%%
mean_b = b / length(msg);
%%
results = [b n mean_b ralph_entropy ralph_redundancy];
%%
save('results.txt','results','-ascii');
