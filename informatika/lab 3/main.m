%% N0%%
V = 80;

%% N1%%
rand ("state", V) 

%% N2%%
a = 1:100;
b = randi([0, 1], 1, 150);
c = a + b;
c(mod(c,2) == 1) = 0;

%% N3%%
r = 4*rand(1, 88*V);
f = @(t) sum(r < t);
x = 0:0.1:4;
y = arrayfun(f, x);

plot(x,y);
grid on;
xlabel('X');
ylabel('Y');
title('N3');
print -dpng 3.png;

%% N4%%
figure;
plot(rand(18,3), rand(18,3), '-*'); 
grid on;
xlabel('X');
ylabel('Y');
title('N4');
print -dpng 4.png;

%% N5%%
figure; 
plot3(rand(18,3), rand(18,3),rand(18,3), '-s'); 
grid on;
xlabel('X');
ylabel('Y');
zlabel('Z');
title('N5');
print -dpng 5.png;

%% N6%%
t = 0:0.01:10*pi;
x=t.* cos(t);
y=t.* sin(t);

figure;
plot(x,y, '--r');
grid on;
xlabel('X');
ylabel('Y');
title('N6');
axis square;
print -dpng 6.png;

%% N7.1
[X, Y] = meshgrid (-4:0.1:4);
Z = cos(0.5*V*X).*X.^3 + Y.^2;

figure;
mesh(X, Y ,Z);
grid on;
xlabel('X');
ylabel('Y');
zlabel('Z');
title 'z = cos(1.2)*x^3 - y^2';
print -dpng 7_1.png;

%% N7.2%%
figure;
surf(X, Y, Z);
grid on;
xlabel('X');
ylabel('Y');
zlabel('Z');
title 'z = cos(1.2)*x^3 - y^2';
print -dpng 7_2.png;

%% N11%%
s = flip_stats(24, 904);

figure;
bar(s/904);
grid on;
xlabel('X');
ylabel('Y');
title('N11: ');
print -dpng 11.png;

% zadanie na zachity 1/3/1/2/2%%
res = [1 2 3 0.1; 4 5 6 0.5; 7 8 10 0.6; 9 6 3 0.5; 3 4 5 0.1; 1 2 3 0.3];

m = flip_matrix_if(res);
