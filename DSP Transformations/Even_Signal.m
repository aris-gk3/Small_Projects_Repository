clc;
clear all;
close all;
t=-10:0.1:10;
A=0.8;
x1=cos(t);
x2=cos(-t);
if(x2==x1)
    disp('The given signal is even signal');
else
    if(x2==(-x1))
        disp('The given signal is odd signal');
    else
        disp('The given signal is neither even nor odd');
    end
end
xe=(x1+x2)/2;
xo=(x1-x2)/2;

subplot(2,2,1);
plot(t,x1);
xlabel('t');
ylabel('x(t)');
title('signal x(t)');

subplot(2,2,2);
plot(t,x2);
xlabel('t');
ylabel('x(t)');
title('signal x(-t)');

subplot(2,2,3);
plot(t,xe);
xlabel('t');
ylabel('x(t)');
title('even part signal x(t)');

subplot(2,2,4);
plot(t,xo);
xlabel('t');
ylabel('x(t)');
title('odd part signal x(t)');