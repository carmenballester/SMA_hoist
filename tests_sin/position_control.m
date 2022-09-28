% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
signal_1 = position_control_get_data();

%% DEFINE VARIABLES
% Cutdown plots
f = str2double(signal_1.f_s);
sat = input('Saturation? ');

if sat
    num_cicles = 10;
    limit_time = round(6.2814*num_cicles/f);
    
    t = signal_1.t(1:find(signal_1.t==limit_time));
    pos = signal_1.pos(1:find(t==limit_time));
    ref = signal_1.ref(1:find(t==limit_time));
    c = signal_1.c(1:find(t==limit_time));
    int = signal_1.int(1:find(t==limit_time)) *5/4096;
    e = signal_1.e(1:find(t==limit_time));
    ep = signal_1.ep(1:find(t==limit_time));

else
    t = signal_1.t;
    pos = signal_1.pos;
    ref = signal_1.ref;
    c = signal_1.c;
    int = signal_1.int;
    e = signal_1.e;
    ep = signal_1.ep;
end

pos_nc = signal_1.pos_nc;
t_nc = signal_1.t_nc;

%% PLOTS
% Define colors
outer_space_crayola = [40, 61, 59]/255;
skoleboff = [25, 114, 120]/255;
morning_blue = [131, 168, 166]/255;
champagne_pink = [237, 221, 212]/255;
new_york_pink = [217, 145, 133]/255;
international_orange_golden = [196, 69, 54]/255;
liver_organ = [119, 46, 37]/255;

% Define figure properties
fig_w = 25;
fig_h = 13;
fig_pos = [10 5 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', international_orange_golden, 'LineWidth', 1);
% plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color',skoleboff, 'LineWidth', 1);
% plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
title('\fontsize{18} \bf SMA Position')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Location','southeast')
grid on
xlim([0, t(end)])

% Plot uncontrolled position
upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', international_orange_golden, 'LineWidth', 1);
% plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', skoleboff, 'LineWidth', 1);
% plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
plot(t_nc, pos_nc, '.', 'Color', morning_blue, 'MarkerSize', 5);
% plot(t_nc, pos_nc, '.', 'Color', persian_green, 'MarkerSize', 5);
title('\fontsize{18} \bf SMA Uncontrolled Positions')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t(end)])

% Plot error
err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, c, 'Color', morning_blue, 'LineWidth', 1);
hold on 
plot(t, e*0.01, 'Color', new_york_pink, 'LineWidth', 1);
plot(t, ep*0.01, 'Color', international_orange_golden, 'LineWidth', 0.5);
title('\fontsize{18} \bf SMA Error')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}Sensor Units')
legend('Control', 'Error','Weighted Error','Location','southeast')
grid on
xlim([0, t(end)])

% Plot control signal
control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, c, 'Color', skoleboff, 'LineWidth', 1);
title('\fontsize{18} \bf PID Control Signal')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}%PWM')
grid on
xlim([0, t(end)])
ylim([min(c) max(c)+10])

% % Plot intensity signal
% int_plot = figure('Name','SMA Intensity Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, int, 'Color', persian_green, 'LineWidth', 1);
% title('\fontsize{18} \bf Intensity Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}A')
% grid on
% xlim([0, t(end)])
% % ylim([0 5.5])

pause;

%% Export to PDF 
export = input('Export? ');
result_name = replace(signal_1.file_name, '.', ',');

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

%     % Control
%     set(control_plot,'PaperSize',pdf_size;
%     print(control_plot, strcat(result_name, '_control'), '-dpdf');
% 
%     % Intensity
%     set(int_plot,'PaperSize',pdf_size);
%     print(int_plot, strcat(result_name, '_int'), '-dpdf');
end