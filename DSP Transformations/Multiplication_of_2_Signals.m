% Multiplication of two signals
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
x4=x1.*x2;                           %".*" this type of multiplication in matrices mulitplies cell by cell
subplot(2,1,2);                      %only the ones that have same cell number so amplitudes that correspond
plot(t,x4);                          %to the same time instance
xlabel('t');
ylabel('amplitude');
title('The multiplication of x1(t) and x2(t)');