% Generation of unit impulse, unit step, and unit ramp Sequences
clc;
clear all;
close all;
n=-10:1:10;
L=length(n);
for i=1:L
    if n(i)==0
        x1(i)=1;
    else x1(i)=0;
    end;
    if n(i)>=0
        x2(i)=1;
        x3(i)=n(i);
    else x2(i)=0;
        x3(i)=0;
    end;
end;
figure;
stem(n,x1);
xlabel(' n ---->');
ylabel('amplitude---->');
title('Unit-impulse signal');