% Plot results with controlled positions
clc, close all

% folder_path = 'G:\Mi unidad\SMA Carmen\polipasto_v2\tests_sin\test_8hilos_0.31d_30cm_3vueltas_54000us\';
% load(strcat(folder_path, '0.1f_0.50kg.mat'))

% Define colors
charcoal = [38 70 83]/255;
persian_green = [42 157 143]/255;
maize_crayola = [233 196 106]/255;
sandy_brown = [244 162 97]/255;
burnt_sienna = [231 111 81]/255;

% Define saturation
sat = 0;
max_time = 600.00;

if sat == true
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));
    pos = POSICION.signals.values(1:find(t==max_time));
    ref = REFERENCIA.signals.values(1:find(t==max_time));
    c = CONTROL.signals.values(1:find(t==max_time));
    int = INTENSIDAD.signals.values(1:find(t==max_time)) *5/4096;
    e = ERROR.signals.values(1:find(t==max_time));
    ep = ERROR_PONDERADO.signals.values(1:find(t==max_time));

else
    t = single(POSICION.time);
    pos = POSICION.signals.values;
    ref = REFERENCIA.signals.values;
    c = CONTROL.signals.values;
    int = INTENSIDAD.signals.values *5/4096;
    e = ERROR.signals.values;
    ep = ERROR_PONDERADO.signals.values;
end
% 
% t = single(Posicion.time);
% pos = Posicion.signals.values;
% ref = referencia.signals.values(:,3);
% c = control.signals.values(:,2);
% ep = error_ponderado.signals.values;
% 
% e = ref-pos;

% Get uncontrolled positions
index = find(c == 0.0);
pos_nc = pos(index);
t_nc = t(index);

% Plot position
figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
title('\fontsize{18} \bf SMA Position')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}Sensor Units')
legend('Reference','Measured position','Location','southeast')
grid on
xlim([0, t(end)])
% ylim([min(pos) max([max(pos) ,max(ref)])+100])

% Plot uncontrolled position
figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
plot(t, ref, 'Color', burnt_sienna, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', charcoal, 'LineWidth', 1);
plot(t_nc, pos_nc, '.', 'Color', persian_green, 'MarkerSize', 5);

title('\fontsize{18} \bf SMA Uncontrolled Positions')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}Sensor Units')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t(end)])
% ylim([min(pos) max([max(pos) ,max(ref)])+100])

% Plot error
figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
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
% ylim([min(min(e), min(ep), min(c)) max(max(e), max(ep), max(c))+10])

% Plot control signal
figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
plot(t, c, 'Color', persian_green, 'LineWidth', 1);
title('\fontsize{18} \bf PID Control Signal')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}%PWM')
grid on
xlim([0, t(end)])
ylim([min(c) max(c)+10])

% Plot intensity signal
% figure('Name','SMA Intensity Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
% plot(t, int, 'Color', persian_green, 'LineWidth', 1);
% title('\fontsize{18} \bf Intensity Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}A')
% grid on
% xlim([0, t(end)])
% % ylim([0 5.5])