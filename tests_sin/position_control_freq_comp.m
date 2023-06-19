% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
signal = get_signal_data();

%% DEFINE VARIABLES
% Cutdown plots
f = str2double(signal.f_s);
sat = input('Saturation? ');

if sat
    limit_time = 300;
    
    t = signal.t(1:find(signal.t==limit_time));
    pos = signal.pos(1:find(t==limit_time));
    ref = signal.ref(1:find(t==limit_time));
    c = signal.c(1:find(t==limit_time));
    int = signal.int(1:find(t==limit_time)) *5/4096;
    e = signal.e(1:find(t==limit_time));
    ep = signal.ep(1:find(t==limit_time));

else
    t = signal.t;
    pos = signal.pos;
    ref = signal.ref;
    c = signal.c;
    int = signal.int;
    e = signal.e;
    ep = signal.ep;
end

pos_nc = signal.pos_nc;
t_nc = signal.t_nc;

%% PLOTS
% Define colors
light_sea_green = [32, 171, 161]/255;
space_cadet = [37, 37, 65]/255;
dark_orange = [255, 141, 26]/255;
brick_red = [206, 54, 79]/255;

% Define figure properties
fig_w = 40;
fig_h = 30;
fig_pos = [0 0.0 fig_w fig_h];
pdf_size = [fig_w-4 fig_h-8];

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', space_cadet, 'LineWidth', 1.5);
hold on 
plot(t, pos, 'Color', dark_orange, 'LineWidth', 1.5);
title('\fontsize{30} \bf Actuator response')
xlabel('\fontsize{30}Time (s)')
ylabel('\fontsize{30}Position (cm)')
legend('Reference','Measured position','Location','southeast','FontSize', 25)
grid on
xlim([0, t(end)])
ylim([-0.5, 2.5])
set(gca,'fontsize', 25) 

% Plot uncontrolled position
upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', space_cadet, 'LineWidth', 1.5);
hold on 
plot(t, pos, 'Color', dark_orange, 'LineWidth', 1.5);
plot(t_nc, pos_nc, '.', 'Color', light_sea_green, 'MarkerSize', 6);
title('\fontsize{30} \bf Actuator response')
xlabel('\fontsize{30}Time (s)')
ylabel('\fontsize{30}Position (cm)')
legend('Reference','Measured position','Uncontrolled position','Location','southeast','FontSize', 25)
grid on
xlim([0, t(end)])
set(gca,'fontsize', 25) 

% Plot error
err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, e, 'LineStyle', '--', 'Color', dark_orange, 'LineWidth', 1);
hold on
plot(t, ep, 'LineStyle', '-', 'Color', space_cadet, 'LineWidth', 1);
title('\fontsize{30}\bf Accumulated error during cooling phase' )
xlabel('\fontsize{30}Time (s)')
ylabel('\fontsize{30}Error (cm)')
legend('Real error','Anti-Windup error','Location','southeast','FontSize', 25)
grid on
xlim([0, t(end)])
set(gca,'fontsize', 25) 


% Plot control signal
control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, c, 'Color', space_cadet, 'LineWidth', 1);
title('\fontsize{30} \bf NASS control signal')
xlabel('\fontsize{30}Time')
ylabel('\fontsize{30}%PWM')
grid on
xlim([0, t(end)])
ylim([min(c) max(c)+10])
set(gca,'fontsize', 25) 

% % Plot intensity signal
% int_plot = figure('Name','SMA Intensity Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, int, 'Color', persian_green, 'LineWidth', 1);
% title('\fontsize{18} \bf Intensity Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}A')
% grid on
% xlim([0, t(end)])
% % ylim([0 5.5])

%% Export to PDF 
export = input('Export? ');
result_name = replace(signal.file_name, '.', ',');

if export
    % Position
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, strcat(result_name, '_pos'), '-dpdf');
    
    % Uncontrolled position
    set(upos_plot,'PaperSize',pdf_size);
    print(upos_plot, strcat(result_name, '_upos'), '-dpdf');

    % Error
    set(err_plot,'PaperSize',pdf_size);
    print(err_plot, strcat(result_name, '_err'), '-dpdf');

    % Control
    set(control_plot,'PaperSize',pdf_size);
    print(control_plot, strcat(result_name, '_control'), '-dpdf');
% 
%     % Intensity
%     set(int_plot,'PaperSize',pdf_size);
%     print(int_plot, strcat(result_name, '_int'), '-dpdf');
end