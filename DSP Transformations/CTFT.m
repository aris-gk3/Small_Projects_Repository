clc;
clear all;
close all;
Dt=5*10^(-5); t = -0.005:Dt:0.005; xa = exp(-1000*abs(t));
Wmax = 2*pi*2000; K = 500; k = 0:1:K; W = k*Wmax/K;
Xa = xa * exp(-j*t'*W) * Dt; Xa = real(Xa); %γιατί καταλήγει το Χα συνάρτηση του Ω
W = [-fliplr(W), W(2:501)]; % Omega from -Wmax to Wmax
Xa = [fliplr(Xa), Xa(2:501)]; % Xa over -Wmax to Wmax interval
subplot(2,1,1);plot(t*1000,xa);
xlabel('t in msec'); ylabel('Amplitude')
title('Analog Signal')
subplot(2,1,2);plot(W/(2*pi*1000),Xa*1000);
xlabel('Frequency in KHz'); ylabel('Amplitude (10^-^3)')
title('Continuous-Time Fourier Transform')