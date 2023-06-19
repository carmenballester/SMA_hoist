% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
signal = get_signal_data_pid();

%% DEFINE VARIABLES
% NASS --------------------------------------------------------------------
% Cutdown plots
f = str2double(signal.nass.f_s);
sat = input('Saturation? ');

num_cicles = 3;
limit_time = round(6.2814*num_cicles/f);
T = 1/f * 6.2814/2;

if sat    
    % NASS
    t.nass = signal.nass.t(1:find(signal.nass.t==limit_time));
    pos.nass = signal.nass.pos(1:find(t.nass==limit_time));
    ref.nass = signal.nass.ref(1:find(t.nass==limit_time));
    c.nass = signal.nass.c(1:find(t.nass==limit_time));
    int.nass = signal.nass.int(1:find(t.nass==limit_time)) *5/4096;
    e.nass = signal.nass.e(1:find(t.nass==limit_time));
    ep.nass = signal.nass.ep(1:find(t.nass==limit_time));

    % PID
    t.pid = signal.pid.t(1:find(signal.pid.t==limit_time));
    pos.pid = signal.pid.pos(1:find(t.pid==limit_time));
    ref.pid = signal.pid.ref(1:find(t.pid==limit_time));
    c.pid = signal.pid.c(1:find(t.pid==limit_time));
    int.pid = signal.pid.int(1:find(t.pid==limit_time)) *5/4096;
    e.pid = signal.pid.e(1:find(t.pid==limit_time));
    ep.pid = signal.pid.ep(1:find(t.pid==limit_time));

    x_limits = [0, t.nass(end)];
else
    % NASS
    t.nass = signal.nass.t;
    pos.nass = signal.nass.pos;
    ref.nass = signal.nass.ref;
    c.nass = signal.nass.c;
    int.nass = signal.nass.int;
    e.nass = signal.nass.e;
    ep.nass = signal.nass.ep;

    % PID
    t.pid = signal.pid.t;
    pos.pid = signal.pid.pos;
    ref.pid = signal.pid.ref;
    c.pid = signal.pid.c;
    int.pid = signal.pid.int;
    e.pid = signal.pid.e;
    ep.pid = signal.pid.ep;

    x_limits = [4*T, 6*T];
end

pos_nc.nass = signal.nass.pos_nc;
t_nc.nass = signal.nass.t_nc;

pos_nc.pid = signal.pid.pos_nc;
t_nc.pid = signal.pid.t_nc;


%% PLOTS
% Define colors
light_sea_green = [32, 171, 161]/255;
space_cadet = [37, 37, 65]/255;
dark_orange = [255, 141, 26]/255;

% Define figure properties
h = input('Square (0) or Rectangle (1)?: ');

if h
    fig_w = 40;
    fig_h = 17;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w-4 fig_h];
    font_size_small = 20;
    font_size_large = 25;
else
    fig_w = 20;
    fig_h = 17;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w fig_h];
    font_size_small = 20;
    font_size_large = 25;
end

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t.nass, ref.nass, 'Color', space_cadet, 'LineWidth', 1);
hold on 
plot(t.pid, pos.pid, 'Color',dark_orange, 'LineWidth', 1);
plot(t.nass, pos.nass, 'Color',light_sea_green, 'LineWidth', 1);
title('\bf Actuator Response','FontSize',font_size_large)
xlabel('Time (s)','FontSize',font_size_large)
ylabel('Position (cm)','FontSize',font_size_large)
legend('Reference','PID Controller','NASS Controller','Location','southeast','FontSize', font_size_small)
grid on
xlim(x_limits)
yticklabels({'', '0', '0.5', '1', '1.5', '2', '2.5'})
set(gca,'fontsize', font_size_small)

% Plot error
err_plot = figure('Name','SMA Error','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t.pid, e.pid, 'Color', dark_orange, 'LineWidth', 1);
hold on
plot(t.nass, ep.nass, 'Color', light_sea_green, 'LineWidth', 1);
title('\bf Accumulated error during cooling phase','FontSize', font_size_large)
xlabel('Time (s)','FontSize', font_size_large)
ylabel('Error (cm)','FontSize', font_size_large)
legend('Real error','Anti-Windup error','Location','southeast','FontSize', font_size_small)
grid on
xlim(x_limits)
set(gca,'fontsize', font_size_small) 


% Plot control signal
control_plot = figure('Name','SMA Control Signal','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t.pid, c.pid, 'Color', dark_orange, 'LineWidth', 1);
hold on
plot(t.nass, c.nass, 'Color', light_sea_green, 'LineWidth', 1);
title('\bf PID Control Signal','FontSize',font_size_large)
xlabel('Time','FontSize',font_size_large)
ylabel('%PWM','FontSize',font_size_large)
legend('PID Controller','NASS Controller','Location','southeast','FontSize', font_size_small)
grid on
xlim(x_limits)
ylim([min(c.nass) max(c.nass)+10])
set(gca,'fontsize', font_size_small)

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
result_name = strcat(replace(signal.nass.file_name, '.', ','), '_pid_comp');

if export
    % Position
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, strcat(result_name, '_pos'), '-dpdf');
    
% %     Uncontrolled position
%     set(upos_plot,'PaperSize',pdf_size);
%     print(upos_plot, strcat(result_name, '_upos'), '-dpdf');
% 
% %     Error
%     set(err_plot,'PaperSize',pdf_size);
%     print(err_plot, strcat(result_name, '_err'), '-dpdf');

    % Control
    set(control_plot,'PaperSize',pdf_size);
    print(control_plot, strcat(result_name, '_control'), '-dpdf');
% 
%     % Intensity
%     set(int_plot,'PaperSize',pdf_size);
%     print(int_plot, strcat(result_name, '_int'), '-dpdf');
end