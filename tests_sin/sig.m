clc, clear, close all

t = linspace(-50,50,1000);
one = ones(1,1000);

m = 1;
n = 0;

sigmoid = 1 - one./(1+(exp(-m*(t-n))));

plot(t, sigmoid);

