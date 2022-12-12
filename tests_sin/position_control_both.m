% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
signal = get_signal_data_both();

%% DEFINE VARIABLES
% NASS --------------------------------------------------------------------
% Cutdown plots
f = str2double(signal.nass.f_s);
sat = input('Saturation? ');

if sat
    num_cicles = 10;
    limit_time = round(6.2814*num_cicles/f);
    
    t.nass = signal.nass.t(1:find(signal.nass.t==limit_time));
    pos.nass = signal.nass.pos(1:find(t.nass==limit_time));
    ref.nass = signal.nass.ref(1:find(t.nass==limit_time));
    c.nass = signal.nass.c(1:find(t.nass==limit_time));
    int.nass = signal.nass.int(1:find(t.nass==limit_time)) *5/4096;
    e.nass = signal.nass.e(1:find(t.nass==limit_time));
    ep.nass = signal.nass.ep(1:find(t.nass==limit_time));

else
    t.nass = signal.nass.t;
    pos.nass = signal.nass.pos;
    ref.nass = signal.nass.ref;
    c.nass = signal.nass.c;
    int.nass = signal.nass.int;
    e.nass = signal.nass.e;
    ep.nass = signal.nass.ep;
end

pos_nc.nass = signal.nass.pos_nc;
t_nc.nass = signal.nass.t_nc;

% PID ---------------------------------------------------------------------
% Cutdown plots
f = str2double(signal.pid.f_s);

if sat
    num_cicles = 10;
    limit_time = round(6.2814*num_cicles/f);
    
    t.pid = signal.pid.t(1:find(signal.pid.t==limit_time));
    pos.pid = signal.pid.pos(1:find(t.pid==limit_time));
    ref.pid = signal.pid.ref(1:find(t.pid==limit_time));
    c.pid = signal.pid.c(1:find(t.pid==limit_time));
    int.pid = signal.pid.int(1:find(t.pid==limit_time)) *5/4096;
    e.pid = signal.pid.e(1:find(t.pid==limit_time));
    ep.pid = signal.pid.ep(1:find(t.pid==limit_time));

else
    t.pid = signal.pid.t;
    pos.pid = signal.pid.pos;
    ref.pid = signal.pid.ref;
    c.pid = signal.pid.c;
    int.pid = signal.pid.int;
    e.pid = signal.pid.e;
    ep.pid = signal.pid.ep;
end

pos_nc.pid = signal.pid.pos_nc;
t_nc.pid = signal.pid.t_nc;

%% PLOTS
% Define colors
light_sea_green = [32, 171, 161]/255;
space_cadet = [37, 37, 65]/255;
dark_orange = [255, 141, 26]/255;

% Define figure properties
fig_w = 25;
fig_h = 13;
fig_pos = [10 5 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t.nass, ref.nass, 'Color', space_cadet, 'LineWidth', 1);
hold on 
plot(t.nass, pos.nass, 'Color',light_sea_green, 'LineWidth', 1);
plot(t.pid, pos.pid, 'Color',dark_orange, 'LineWidth', 1);
title('\fontsize{18} \bf SMA Position')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','NASS Controller','PID Controller','Location','southeast')
grid on
xlim([0, t.nass(end)])

% % Plot uncontrolled position
% upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t.nass, ref.nass, 'Color', international_orange_golden, 'LineWidth', 1);
% % plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
% hold on 
% plot(t.nass, pos.nass, 'Color', skoleboff, 'LineWidth', 1);
% % plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
% plot(t_nc.nass, pos_nc.nass, '.', 'Color', morning_blue, 'MarkerSize', 5);
% % plot(t_nc, pos_nc, '.', 'Color', persian_green, 'MarkerSize', 5);
% title('\fontsize{18} \bf SMA Uncontrolled Positions')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}cm')
% legend('Reference','Measured position','Uncontrolled position','Location','southeast')
% grid on
% xlim([0, t(end)])
% 
% % Plot error
% err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t.nass, c.nass, 'Color', morning_blue, 'LineWidth', 1);
% hold on 
% plot(t.nass, e.nass*0.01, 'Color', new_york_pink, 'LineWidth', 1);
% plot(t.nass, ep.nass*0.01, 'Color', international_orange_golden, 'LineWidth', 0.5);
% title('\fontsize{18} \bf SMA Error')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}Sensor Units')
% legend('Control', 'Error','Weighted Error','Location','southeast')
% grid on
% xlim([0, t(end)])

% % Plot control signal
% control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, c, 'Color', skoleboff, 'LineWidth', 1);
% title('\fontsize{18} \bf PID Control Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}%PWM')
% grid on
% xlim([0, t(end)])
% ylim([min(c) max(c)+10])

% % Plot intensity signal
% int_plot = figure('Name','SMA Intensity Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, int, 'Color', persian_green, 'LineWidth', 1);
% title('\fontsize{18} \bf Intensity Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}A')
% grid on
% xlim([0, t(end)])
% % ylim([0 5.5])

% %% Export to PDF 
% export = input('Export? ');
% result_name = replace(signal.file_name, '.', ',');
% 
% if export
%     % Position
%     set(pos_plot,'PaperSize',pdf_size);
%     print(pos_plot, strcat(result_name, '_pos'), '-dpdf');
%     
%     % Uncontrolled position
%     set(upos_plot,'PaperSize',pdf_size);
%     print(upos_plot, strcat(result_name, '_upos'), '-dpdf');
% 
%     % Error
%     set(err_plot,'PaperSize',pdf_size);
%     print(err_plot, strcat(result_name, '_err'), '-dpdf');
% 
% %     % Control
% %     set(control_plot,'PaperSize',pdf_size;
% %     print(control_plot, strcat(result_name, '_control'), '-dpdf');
% % 
% %     % Intensity
% %     set(int_plot,'PaperSize',pdf_size);
% %     print(int_plot, strcat(result_name, '_int'), '-dpdf');
% end