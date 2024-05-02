% Shifting of two signals
clc;
close all;
clear all;
t=0:0.001:1;
L=length(t);
f1=1;
f2=3;
x1=sin(2*pi*f1*t);
x2=sin(2*pi*f2*t);
figure;
subplot(2,1,1);
plot(t,x1,'b',t,x2,'r');
xlabel('t');
ylabel('amplitude');
title('The signals x1(t) and x2(t)');
x3=[zeros(1,100),x2(1:L-100)];      %here we know the cell that corresponds to the time shifting we want is 102
x4=[zeros(1,100),x1(1:L-100)];
subplot(2,1,2);
plot(t,x3,'b',t,x4,'r');
title('the shifting of x1(t)and x2(t)');
xlabel('t');
ylabel('amplitude');