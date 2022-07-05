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
n = 3; % My number of turns

s = zeros(length(N), length(l)); % Displacement

% Define graphic variables
color_plot_s = zeros(length(N), 3);

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

%% PLOTS 
fig_w = 25;
fig_h = 13;
fig_pos = [10 5 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

% Displacement lineal
% disp_plot = figure('Name','A','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(l,s)
% colororder(color_plot_s)
% title('\fontsize{18} \bf Displacement')
% xlabel('\fontsize{16}SMA wire length')
% ylabel('\fontsize{16}cm')
% legend('Single SMA Actuator','', ...
%        'Parallel Hoist SMA Actuator (3 turns)', ...
%        'Parallel Hoist SMA Actuator (n turns)', ...
%        'Location','northwest')
% grid off
% xlim([1, l(end)])
%% Bar
% Get data

% R = zeros(length(N));
R = 0.03*N*100;

for i=1:length(N) 
%     R(i,i) = 0.03*i*100;
    if i == 1
        color_plot_s(i,:) = morning_blue(1,:);
    elseif i == n
        color_plot_s(i,:) = new_york_pink(1,:);
    else
        color_plot_s(i,:) = champagne_pink(1,:);
    end
end

% Displacement bar
disp_bar = figure('Name','Parallel Hoist SMA Actuator Displacement','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
b = barh(N',R',0.4,'FaceColor','flat');
% for i=1:length(N) 
%     b.CData(i,:) = color_plot_s(i,:);
% end

title('\fontsize{18} \bfRelation between SMA lenght and displacement')
xlabel('\fontsize{16}Percent of displacement')
ylabel('\fontsize{16}Number of hoist turns')
legend('Single SMA Actuator','', ...
       'Parallel Hoist SMA Actuator (3 turns)', ...
       'Parallel Hoist SMA Actuator (n turns)', ...
       'Location','southeast')
grid off
xlim([1, R(end)])