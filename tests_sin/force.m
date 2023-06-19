% Probando cosas
clear, clc, close all

% Define colors
space_cadet = [37, 37, 65]/255 ;
light_sea_green = [32, 171, 161]/255;
bisque = [255, 225, 194]/255;
dark_orange = [255, 141, 26]/255;
brick_red = [206, 54, 79]/255;
ocean_blue = [73, 56, 181]/255;

% Define physic variables
N = 1:0.01:5; % Numero de vueltas del polipasto
N_d = 1:1:5; % Numero de vueltas del polipasto discreto
h = 0:1:12; % Numero de hilos del actuador
n = 8; % My number of wires

F_max = zeros(length(h), length(N)); % Force
F_rec = zeros(length(h), length(N)); % Force

F_max_d = zeros(length(h), length(N_d)); % Force
F_rec_d = zeros(length(h), length(N_d)); % Force

% Define graphic variables
color_plot_F = zeros(length(h), 3);

%% GET DATA
% Maximum Force
for i=1:length(h) 
    F_max(i,:) = 2.25*i./N;
    F_max_d(i,:) = 2.25*i./N_d;
    if i == 1
        color_plot_F(i,:) = light_sea_green(1,:);
    elseif i == n
        color_plot_F(i,:) = dark_orange(1,:);
    else
        color_plot_F(i,:) = bisque(1,:);
    end
end

% Minimum Force
for i=1:length(h) 
    F_rec(i,:) = 0.9*i.*N;
    F_rec_d(i,:) = 0.9*i.*N_d;
    if i == 1
        color_plot_F(i,:) = light_sea_green(1,:);
    elseif i == n
        color_plot_F(i,:) = dark_orange(1,:);
    else
        color_plot_F(i,:) = bisque(1,:);
    end
end

% F_max = normr(F_max);
% F_max_d = normr(F_max_d);

F_dif = - F_rec + F_max;
F_dif_d = - F_rec_d + F_max_d;

%% PLOTS 
fig_w = 20;
fig_h = 30;
fig_pos = [0 0 fig_w fig_h];
pdf_size = [fig_w fig_h-9];

% Force max
force_max_plot = figure('Name','Paraller Hoist SMA Actuator Forces','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(N,F_max,'--','LineWidth',1)
hold on
plot(N_d,F_max_d,'.','MarkerSize',35);
colororder(color_plot_F)
xlabel('\fontsize{30}Number of hoist turns')
ylabel('\fontsize{30}Heating pull force (kg)')
legend('','','','','','','','','Theorical curves','','','','', ...
       'Single SMA Actuator','','','','','','', ...
       'Parallel Hoist SMA Actuator (8 wires)', ...
       'Parallel Hoist SMA Actuator (h wires)', ...
       'Location','northwest', ...
        'FontSize', 20)
grid off
xlim([1, N(end)])
set(gca,'fontsize', 25) 
grid on

% Force rec
force_rec_plot = figure('Name','Paraller Hoist SMA Actuator Forces','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(N,F_rec, '--', 'LineWidth',1)
hold on
plot(N_d,F_rec_d,'.','MarkerSize',35);
colororder(color_plot_F)
xlabel('\fontsize{30}Number of hoist turns')
ylabel('\fontsize{30}Cooling deformation force (kg)')
legend('','','','','','','','','Theorical curves','','','','', ...
       'Single SMA Actuator','','','','','','', ...
       'Parallel Hoist SMA Actuator (8 wires)', ...
       'Parallel Hoist SMA Actuator (h wires)', ...
       'Location','northwest', ...
        'FontSize', 20)
grid off
xlim([1, N(end)])
set(gca,'fontsize', 25) 
grid on

% Force rec
force_dif_plot = figure('Name','Paraller Hoist SMA Actuator Forces','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(N,F_dif, '--', 'LineWidth',1)
hold on
plot(N_d,F_dif_d,'.','MarkerSize',35);
colororder(color_plot_F)
xlabel('\fontsize{30}Number of hoist turns')
ylabel('\fontsize{30}Force advantage (kg)')
legend('','','','','','','','','Theorical curves','','','','', ...
       'Single SMA Actuator','','','','','','', ...
       'Parallel Hoist SMA Actuator (8 wires)', ...
       'Parallel Hoist SMA Actuator (h wires)', ...
       'Location','southwest', ...
        'FontSize', 20)
grid off
xlim([1, N(end)])
set(gca,'fontsize', 25) 
grid on

%% Export to PDF 
export = input('Export? ');
result_name = 'force_comp';

if export
    set(force_max_plot,'PaperSize',pdf_size);
    print(force_max_plot, strcat(result_name, '_max'), '-dpdf');

    set(force_rec_plot,'PaperSize',pdf_size);
    print(force_rec_plot, strcat(result_name, '_rec'), '-dpdf');

    set(force_dif_plot,'PaperSize',pdf_size);
    print(force_dif_plot, strcat(result_name, '_dif'), '-dpdf');
    
end