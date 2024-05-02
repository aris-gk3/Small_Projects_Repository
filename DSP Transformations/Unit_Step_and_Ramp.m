%generate unit Step
clc;                  %clears the command window
clear all;            %clears all the workspace
close all;            %closes all windows
t=-20:0.01:20; 
for i=1:length(t)     %cell of matrices begin from 1
    if t(i)<0
        x1(i)=0;
        x2(i)=0;
    else
        x1(i)=1;
        x2(i)=t(i);
    end;
end;
figure;              %creates a graphic representation
plot(t,x1);          %plots it
xlabel('t');
ylabel('amplitude');
title('unit step');
figure;              %creates a graphic representation
plot(t,x2);          %plots it
xlabel('t');
ylabel('amplitude');
title('ramp');
grid 