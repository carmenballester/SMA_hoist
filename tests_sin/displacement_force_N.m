% Probando cosas
clear, clc, close all

% Define colors
outer_space_crayola = [40, 61, 59]/255;
skoleboff = [25, 114, 120]/255;
morning_blue = [131, 168, 166]/255;
champagne_pink = [237, 221, 212]/255;
new_york_pink = [217, 145, 133]/255;
international_orange_golden = [196, 69, 54]/255;
liver_organ = [119, 46, 37]/255;

% Define physic variables
N = 1:1:5; % Numero de vueltas del polipasto
l = 1:0.1:100; % cm de longitud del hilo
h = 0:1:12; % Numero de hilos del actuador
n = 3; % My number of turns

s = zeros(length(N), length(l)); % Displacement
F_max = zeros(length(N), length(h)); % Force
F_rec = zeros(length(N), length(h)); % Force

% Define graphic variables
color_plot_s = zeros(length(N), 3);
color_plot_F = zeros(length(h), 3);

%% GET DATA
% Displacement
for i=1:length(N) 
    s(i,:) = 0.03*i*l;
    if i == 1
        color_plot_s(i,:) = skoleboff(1,:);
    elseif i == n
        color_plot_s(i,:) = international_orange_golden(1,:);
    else
        color_plot_s(i,:) = champagne_pink(1,:);
    end
end

% Maximum Force
for i=1:length(N) 
    F_max(i,:) = 1.3*h./i;
    if i == 1
        color_plot_F(i,:) = skoleboff(1,:);
    elseif i == n
        color_plot_F(i,:) = international_orange_golden(1,:);
    else
        color_plot_F(i,:) = champagne_pink(1,:);
    end
end

% Minimum Force
for i=1:length(N) 
    F_rec(i,:) = 0.512*h.*i;
    if i == 1
        color_plot_F(i,:) = skoleboff(1,:);
    elseif i == n
        color_plot_F(i,:) = international_orange_golden(1,:);
    else
        color_plot_F(i,:) = champagne_pink(1,:);
    end
end

%% PLOTS 
fig_w = 25;
fig_h = 13;
fig_pos = [10 5 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

% Displacement
disp_plot = figure('Name','A','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
disp_sp = subplot(1,3,1); 
plot(l,s)
colororder(color_plot_s)
title('\fontsize{18} \bf Displacement')
xlabel('\fontsize{16}SMA wire length')
ylabel('\fontsize{16}cm')
legend('N=1','N=2','N=3','N=4','N=5','Location','northwest')
grid off
xlim([0, l(end)])

% Force max
force_max_sb = subplot(1,3,2);
plot(h,F_max)
colororder(color_plot_F)
title('\fontsize{18} \bf Maximum Force')
xlabel('\fontsize{16}Number of SMA wires')
ylabel('\fontsize{16}kg')
legend('N=1','N=2','N=3','N=4','N=5','Location','northwest')
grid off
xlim([0, h(end)])

% Force rec
force_rec_sb = subplot(1,3,3);
plot(h,F_rec)
colororder(color_plot_F)
title('\fontsize{18} \bf Recovery Force')
xlabel('\fontsize{16}Number of SMA wires')
ylabel('\fontsize{16}kg')
legend('N=1','N=2','N=3','N=4','N=5','Location','northwest')
grid off
xlim([0, h(end)])
