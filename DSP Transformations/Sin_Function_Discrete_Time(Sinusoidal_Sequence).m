clc;
clear all;
close all;
n=-20:1:20;
L=length(n);
f=0.1;
x1=sin(2*pi*f*n);
stem(n,x1);
xlabel('n');
ylabel('amplitude');
title('sinusoidal signal');