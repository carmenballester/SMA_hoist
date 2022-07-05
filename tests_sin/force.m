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
N = 1:0.01:5; % Numero de vueltas del polipasto
h = 0:1:12; % Numero de hilos del actuador
n = 8; % My number of wires

F_max = zeros(length(h), length(N)); % Force
F_rec = zeros(length(h), length(N)); % Force

% Define graphic variables
color_plot_F = zeros(length(h), 3);

%% GET DATA
% Maximum Force
for i=1:length(h) 
    F_max(i,:) = 1.3*i./N;
    if i == 1
        color_plot_F(i,:) = skoleboff(1,:);
    elseif i == n
        color_plot_F(i,:) = international_orange_golden(1,:);
    else
        color_plot_F(i,:) = champagne_pink(1,:);
    end
end

% Minimum Force
for i=1:length(h) 
    F_rec(i,:) = 0.512*i.*N;
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

% Force max
force_plot = figure('Name','Paraller Hoist SMA Actuator Forces','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
force_max_sb = subplot(1,2,1);
plot(N,F_max)
colororder(color_plot_F)
title('\fontsize{18} \bf Maximum Force')
xlabel('\fontsize{16}Number of hoist turns')
ylabel('\fontsize{16}kg')
legend('Single SMA Actuator','','','','','','', ...
       'Parallel Hoist SMA Actuator (8 wires)', ...
       'Parallel Hoist SMA Actuator (h wires)', ...
       'Location','northwest')
grid off
xlim([1, N(end)])

% Force rec
force_rec_sb = subplot(1,2,2);
plot(N,F_rec)
colororder(color_plot_F)
title('\fontsize{18} \bf Recovery Force')
xlabel('\fontsize{16}Number of hoist turns')
ylabel('\fontsize{16}kg')
legend('Single SMA Actuator','','','','','','','Parallel Hoist SMA Actuator (8 wires)','Parallel Hoist SMA Actuator (h wires)','Location','northwest')
grid off
xlim([1, N(end)])

%% Export to PDF 
export = input('Export? ');
result_name = 'bowden_comparison';

if export
    % Force
    set(force_plot,'PaperSize',pdf_size);
    print(force_plot, strcat(result_name, '_force'), '-dpdf');
    
end