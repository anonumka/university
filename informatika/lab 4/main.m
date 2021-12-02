V = 3;
%% initialization rnd%%
rand ("state", V);

%% %%
r = rand(1, 10);
r = r / sum(r);
save('ralph.txt','r','-ascii');

%%

coin = load('coin.txt', '-ascii');
res = [alph_entropy(coin), alph_redundancy(coin)];

crime = load('crime.txt', '-ascii');
res = [res; alph_entropy(crime), alph_redundancy(crime)];

unfair = load('unfair.txt', '-ascii');
res = [res; alph_entropy(unfair), alph_redundancy(unfair)];

ventsel = load('ventsel.txt', '-ascii');
res = [res; alph_entropy(ventsel), alph_redundancy(ventsel)];

ralph = load('ralph.txt', '-ascii');
res = [res; alph_entropy(ralph), alph_redundancy(ralph)];

%%
save('results.txt','res','-ascii');