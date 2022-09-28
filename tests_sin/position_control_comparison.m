% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
signal_1 = get_signal_data();
signal_2 = get_signal_data();

%% DEFINE VARIABLES
% Cutdown plots
f_1 = str2double(signal_1.f_s);
f_2 = str2double(signal_2.f_s);
sat = input('Saturation? ');

if sat
    num_cicles = 10;
    limit_time_1 = round(6.2814*num_cicles/f_1);
%     limit_time_2 = round(6.2814*num_cicles/f_2);
    limit_time_2 = limit_time_1;
    
    % Signal 1
    t_1 = signal_1.t(1:find(signal_1.t==limit_time_1));
    pos_1 = signal_1.pos(1:find(t_1==limit_time_1));
    ref_1 = signal_1.ref(1:find(t_1==limit_time_1));
    c_1 = signal_1.c(1:find(t_1==limit_time_1));
    int_1 = signal_1.int(1:find(t_1==limit_time_1)) *5/4096;
    e_1 = signal_1.e(1:find(t_1==limit_time_1));
    ep_1 = signal_1.ep(1:find(t_1==limit_time_1));

    % Signal 2
    t_2 = signal_2.t(1:find(signal_2.t==limit_time_2));
    pos_2 = signal_2.pos(1:find(t_2==limit_time_2));
    ref_2 = signal_2.ref(1:find(t_2==limit_time_2));
    c_2 = signal_2.c(1:find(t_2==limit_time_2));
    int_2 = signal_2.int(1:find(t_2==limit_time_2)) *5/4096;
    e_2 = signal_2.e(1:find(t_2==limit_time_2));
    ep_2 = signal_2.ep(1:find(t_2==limit_time_2));

else
    % Signal 1
    t_1 = signal_1.t;
    pos_1 = signal_1.pos;
    ref_1 = signal_1.ref;
    c_1 = signal_1.c;
    int_1 = signal_1.int;
    e_1 = signal_1.e;
    ep_1 = signal_1.ep;

    % Signal 2
    t_2 = signal_2.t;
    pos_2 = signal_2.pos;
    ref_2 = signal_2.ref;
    c_2 = signal_2.c;
    int_2 = signal_2.int;
    e_2 = signal_2.e;
    ep_2 = signal_2.ep;

end

% Signal 1
pos_nc_1 = signal_1.pos_nc;
t_nc_1 = signal_1.t_nc;

% Signal 2
pos_nc_2 = signal_2.pos_nc;
t_nc_2 = signal_2.t_nc;

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

% Plot position -----------------------------------------------------------
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
sgtitle('\fontsize{14} \bf SMA Response')

subplot(2,1,1);
plot(t_1, ref_1, 'Color', international_orange_golden, 'LineWidth', 1);
hold on 
plot(t_1, pos_1, 'Color',skoleboff, 'LineWidth', 1);
title(strcat('\fontsize{12}\rmf = ',signal_1.f_s,' rad/s; m = ', signal_1.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Position (cm)')
legend('Reference','Measured position','Location','southeast')
grid on
xlim([0, t_1(end)])

subplot(2,1,2)
plot(t_2, ref_2, 'Color', international_orange_golden, 'LineWidth', 1);
hold on 
plot(t_2, pos_2, 'Color',skoleboff, 'LineWidth', 1);
title(strcat('\fontsize{12}\rmf = ',signal_2.f_s,' rad/s; m = ', signal_2.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Position (cm)')
%legend('Reference','Measured position','Location','southeast')
grid on
xlim([0, t_2(end)])

% Plot uncontrolled position-----------------------------------------------
upos_plot = figure('Name','SMA Uncontrolled Positions','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
sgtitle('\fontsize{14} \bf SMA Response')

subplot(2,1,1);
plot(t_1, ref_1, 'Color', international_orange_golden, 'LineWidth', 1);
hold on 
plot(t_1, pos_1, 'Color', skoleboff, 'LineWidth', 1);
plot(t_nc_1, pos_nc_1, '.', 'Color', morning_blue, 'MarkerSize', 5);
title(strcat('\fontsize{12}\rmf = ',signal_1.f_s,' rad/s; m = ', signal_1.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Position (cm)')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t_1(end)])

subplot(2,1,2);
plot(t_2, ref_2, 'Color', international_orange_golden, 'LineWidth', 1);
hold on 
plot(t_2, pos_2, 'Color', skoleboff, 'LineWidth', 1);
plot(t_nc_2, pos_nc_2, '.', 'Color', morning_blue, 'MarkerSize', 5);
title(strcat('\fontsize{12}\rmf = ',signal_2.f_s,' rad/s; m = ', signal_2.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Position (cm)')
legend('Reference','Measured position','Uncontrolled position','Location','southeast')
grid on
xlim([0, t_2(end)])

% Plot error---------------------------------------------------------------
err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
sgtitle('\fontsize{14} \bf SMA Error')

subplot(2,1,1);
plot(t_1, c_1, 'Color', morning_blue, 'LineWidth', 1);
hold on 
plot(t_1, e_1*0.01, 'Color', new_york_pink, 'LineWidth', 1);
plot(t_1, ep_1*0.01, 'Color', international_orange_golden, 'LineWidth', 0.5);
title(strcat('\fontsize{12}\rmf = ',signal_1.f_s,' rad/s; m = ', signal_1.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Error (\mum)')
legend('Control', 'Error','Weighted Error','Location','southeast')
grid on
xlim([0, t_1(end)])

subplot(2,1,2);
plot(t_2, c_2, 'Color', morning_blue, 'LineWidth', 1);
hold on 
plot(t_2, e_2*0.01, 'Color', new_york_pink, 'LineWidth', 1);
plot(t_2, ep_2*0.01, 'Color', international_orange_golden, 'LineWidth', 0.5);
title(strcat('\fontsize{12}\rmf = ',signal_2.f_s,' rad/s; m = ', signal_2.m_s,' kg'))
xlabel('\fontsize{10}Time (s)')
ylabel('\fontsize{10}Error (\mum)')
%legend('Control', 'Error','Weighted Error','Location','southeast')
grid on
xlim([0, t_2(end)])

% % Plot control signal
% control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% plot(t_1, c_1, 'Color', skoleboff, 'LineWidth', 1);
% title('\fontsize{18} \bf PID Control Signal')
% xlabel('\fontsize{16}Time')
% ylabel('\fontsize{16}%PWM')
% grid on
% xlim([0, t_1(end)])
% ylim([min(c_1) max(c_1)+10])
% 
% % % Plot intensity signal
% % int_plot = figure('Name','SMA Intensity Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% % plot(t, int, 'Color', persian_green, 'LineWidth', 1);
% % title('\fontsize{18} \bf Intensity Signal')
% % xlabel('\fontsize{16}Time')
% % ylabel('\fontsize{16}A')
% % grid on
% % xlim([0, t(end)])
% % % ylim([0 5.5])
% 
% pause;
% 
%% Export to PDF 
export = input('Export? ');
result_name = strcat(replace(signal_1.file_name, '.', ','), 'comparison');

if export
    % Position
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, strcat(result_name, '_pos'), '-dpdf');
    
%     % Uncontrolled position
%     set(upos_plot,'PaperSize',pdf_size);
%     print(upos_plot, strcat(result_name, '_upos'), '-dpdf');

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