clc;
clear all;
close all;
num=input('type the numerator vector');
%num=[1 3 -3 2 5 -2 2 4 -4]
den=input('type the denominator vector'); %the transfer function is a fraction of two polynomials that have the given coefficients 
%den=1
N=input(' enter the desired length of the output sequence');
%N=12
n=0:N-1;              
imp=[1 zeros(1,N-1)];
H=filter(num, den, imp);   %H is the impulse reaction of the transfer fanction with coeffecients of the polynomials given as arguments
disp(' the impulse response of the system is ');
disp(H);
stem(n,H);
xlabel('n');
ylabel('h(n)');
title(' Impulse response'); 