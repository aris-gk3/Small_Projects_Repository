clc;
clear all;
close all;
n=-5:1:15;
L=length(n);
for i=1:L
    if n(i)>=0
        x1(i)=1;
        x2(i)=n(i);
    else
        x1(i)=0;
        x2(i)=0;
    end;
end;
figure;
subplot(2,1,1);
stem(n,x1);
xlabel('n');
ylabel('amplitude');
title('Unit step signal');
subplot(2,1,2);
stem(n,x2);
xlabel('n');
ylabel('amplitude');
title('Unit ramp signal');
grid;