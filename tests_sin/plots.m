% Plot results with controlled positions
clear, clc, close all

%% Load data
% Get data parameters
f_s = input('Frecuencia: ','s');
m_s = input('Masa: ', 's');

% Define paths
folder_path = 'G:\Mi unidad\SMA Carmen\polipasto_v2\tests_sin\test_8hilos_0.31d_30cm_3vueltas_54000us_good_control\';
file_name = strcat(f_s, 'f_', m_s, 'kg');
file_path = strcat(folder_path, file_name, '.mat');

% Load specifyed data
load(file_path);

% Define colors
charcoal = [38 70 83]/255;
persian_green = [42 157 143]/255;
maize_crayola = [233 196 106]/255;
sandy_brown = [244 162 97]/255;
burnt_sienna = [231 111 81]/255;

% Define saturation
sat = input('Saturation? ');
max_time = 600.00;
% num_ciclos = 10;
% frec = 0.3;
% max_time = round(6.2814*num_ciclos/frec);

if sat
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));
    pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
    ref = REFERENCIA.signals.values(1:find(t==max_time))*0.48*10^-4;
    c = CONTROL.signals.values(1:find(t==max_time));
    int = INTENSIDAD.signals.values(1:find(t==max_time)) *5/4096;
    e = ERROR.signals.values(1:find(t==max_time));
    ep = ERROR_PONDERADO.signals.values(1:find(t==max_time));

else
    t = single(POSICION.time);
    pos = POSICION.signals.values*0.48*10^-4;
    ref = REFERENCIA.signals.values*0.48*10^-4;
    c = CONTROL.signals.values;
    int = INTENSIDAD.signals.values *5/4096;
    e = ERROR.signals.values;
    ep = ERROR_PONDERADO.signals.values;
end

% t = single(Posicion.time);
% pos = Posicion.signals.values;
% ref = referencia.signals.values(:,3);
% c = control.signals.values(:,2);
% ep = error_ponderado.signals.values;

% e = ref-pos;

% Get uncontrolled positions
index = find(c == 0.0);
pos_nc = pos(index);
t_nc = t(index);

%% PLOTS
fig_pos = [10 5 16 13];
pdf_size = [17 14];

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
title('\fontsize{18} \bf SMA Position')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Location','southeast')
grid on
xlim([0, t(end)])

% Plot uncontrolled position
upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
plot(t_nc, pos_nc, '.', 'Color', persian_green, 'MarkerSize', 5);
title('\fontsize{18} \bf SMA Uncontrolled Positions')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t(end)])

% Plot error
err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, c, 'Color', persian_green, 'LineWidth', 1);
hold on 
plot(t, e*0.01, 'Color', maize_crayola, 'LineWidth', 1);
plot(t, ep*0.01, 'Color', sandy_brown, 'LineWidth', 1);
title('\fontsize{18} \bf SMA Error')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}Sensor Units')
legend('Control', 'Error','Weighted Error','Location','southeast')
grid on
xlim([0, t(end)])

% % Plot control signal
% control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t, c, 'Color', persian_green, 'LineWidth', 1);
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

%% Export to PDF 
export = input('Export? ');
result_name = replace(file_name, '.', ',');

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