clc, close all

%% DEFINE VARIABLESn   
% Cutdown plots
f = frec;

t = single(POSICION.time);
max_time = t(end);

t = single(POSICION.time(1:find(t==max_time)));
pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
ref = REFERENCIA.signals.values(1:find(t==max_time))*0.48*10^-4;
c = CONTROL.signals.values(1:find(t==max_time));
int = INTENSIDAD.signals.values(1:find(t==max_time)) *5/4096;
e = ERROR.signals.values(1:find(t==max_time));
ep = ERROR_PONDERADO.signals.values(1:find(t==max_time));
% temp = TEMPERATURA.signals.values(1:find(t==max_time));
% ep = e./(1+exp(-0.05*(e+500)));
% Get uncontrolled positions
index = find(c == 0.0);
pos_nc = pos(index);
t_nc = t(index);

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

% % Plot position
% pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, ref, 'Color', international_orange_golden, 'LineWidth', 1);
% % plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
% hold on 
% plot(t, pos, 'Color',skoleboff, 'LineWidth', 1);
% % plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
% title('\fontsize{18} \bf SMA Position')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}cm')
% legend('Reference','Measured position','Location','southeast')
% grid on
% xlim([0, t(end)])

% % Plot temperature
% temp_plot = figure('Name','SMA Temperature','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, temp, 'Color', international_orange_golden, 'LineWidth', 1);
% title('\fontsize{18} \bf SMA Temperature')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}�C')
% grid on
% xlim([0, t(end)])

% Plot uncontrolled position
upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', international_orange_golden, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', skoleboff, 'LineWidth', 1);
plot(t_nc, pos_nc, '.', 'Color', morning_blue, 'MarkerSize', 5);
title('\fontsize{18} \bf SMA Uncontrolled Positions')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t(end)])

% % Plot error
% err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, c, 'Color', morning_blue, 'LineWidth', 1);
% hold on 
% plot(t, e*0.01, 'Color', new_york_pink, 'LineWidth', 1);
% plot(t, ep*0.01, 'Color', international_orange_golden, 'LineWidth', 0.5);
% title('\fontsize{18} \bf SMA Error')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}Sensor Units')
% legend('Control', 'Error','Weighted Error','Location','southeast')
% grid on
% xlim([0, t(end)])

% Plot control signal
control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, c, 'Color', skoleboff, 'LineWidth', 1);
hold on 
plot(t, int, 'Color', skoleboff, 'LineWidth', 1);
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
