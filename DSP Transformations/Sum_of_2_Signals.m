%Sum of two signals
clc;
close all;
clear all;
t=0:0.001:1;
L=length(t);
f1=1;               %frequency of first signal
f2=3;               %frequency of second signal
x1=sin(2*pi*f1*t);  %x1 is now a matrix containg the values, cell numbers tie amplitude values to time
x2=sin(2*pi*f2*t);  %same for x2
figure;
subplot(2,1,1);
plot(t,x1,'b',t,x2,'r');
xlabel('t');
ylabel('amplitude');
title('The signals x1(t) and x2(t)');
x3=x1+x2;
subplot(2,1,2);
plot(t,x3);
xlabel('t');
ylabel('amplitude');
title('The sum of x1(t) and x2(t)'); 