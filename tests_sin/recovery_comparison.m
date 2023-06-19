% Get significant values of data and plot results
clear, clc, close all

%% LOAD DATA
signal_1 = get_signal_data();
signal_2 = get_signal_data();

%% DEFINE VARIABLES
% Cutdown plots
f_1 = str2double(signal_1.f_s);
f_2 = str2double(signal_2.f_s);

T_1 = single(round(1/f_1 * 6.2814/2, 2));
T_2 = single(round(1/f_2 * 6.2814/2, 2));

sat = input('Saturation? ');
if sat
%     num_cicles = 30;
%     max_time = 2*T_1*num_cicles;

    max_time = 300;
    num_cicles = max_time/(2*T_1);

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
    max_time = 600.00;

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

%% COMPUTE RECOVERY FITTING
% Get recovery values
min_t_1 = [];
min_pos_1 = [];
cicles_1 = round((max_time/T_1));

min_t_2 = [];
min_pos_2 = [];
cicles_2 = round((max_time/T_2));

for j=0:2:cicles_1
    t_cicle_1 = t_1(find(t_1==round(j*T_1,2)):find(t_1==round((j+1)*T_1,2)));
    p_cicle_1 = pos_1(find(t_1==round(j*T_1,2)):find(t_1==round((j+1)*T_1,2)));
    r_cicle_1 = ref_1(find(t_1==round(j*T_1,2)):find(t_1==round((j+1)*T_1,2)));

    [min_point, i] = min(p_cicle_1);
    min_pos_1 = [min_pos_1 min_point];
    min_t_1 = [min_t_1 t_cicle_1(i)];
end

for j=0:2:cicles_2
    t_cicle_2 = t_2(find(t_2==round(j*T_2,2)):find(t_2==round((j+1)*T_2,2)));
    p_cicle_2 = pos_2(find(t_2==round(j*T_2,2)):find(t_2==round((j+1)*T_2,2)));
    r_cicle_2 = ref_2(find(t_2==round(j*T_2,2)):find(t_2==round((j+1)*T_2,2)));

    [min_point, i] = min(p_cicle_2);
    min_pos_2 = [min_pos_2 min_point];
    min_t_2 = [min_t_2 t_cicle_2(i)];
end

% Get regression fit
start_points = [1 0.5];

my_fit = fittype('a*atan(b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});

fit_eq_1 = fit(double(min_t_1'), double(min_pos_1'), my_fit, ...
    'Start', start_points, ...
    'Display', 'notify', ...
    'TolFun', 10e-10);
fit_val_1 = feval(fit_eq_1, t_1);

fit_eq_2 = fit(double(min_t_2'), double(min_pos_2'), my_fit, ...
    'Start', start_points, ...
    'Display', 'notify', ...
    'TolFun', 10e-10);
fit_val_2 = feval(fit_eq_2, t_2);

% For comparison
% log_fit2 = fittype('a-exp(-b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});
% f2 = fit(double(min_t'),double(min_pos'),log_fit2, ...
%     'Start', start_points, ...
%     'Display', 'iter', ...
%     'TolFun', 10e-10);

%% PLOTS
% Define colors
light_sea_green = [32, 171, 161]/255;
space_cadet = [37, 37, 65]/255;
dark_orange = [255, 141, 26]/255;

% Define figure properties
fig_w = 40;
fig_h = 15;
fig_pos = [0 0 fig_w fig_h];
pdf_size = [fig_w+0.05 fig_h+0.05];

% Plot recovery curve
rec_plot = figure('Name','SMA Recovery Curve','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
sgtitle('\fontsize{22} \bf SMA Recovery Curve')

subplot(1,2,1);
plot(t_1, ref_1, 'Color', space_cadet, 'LineWidth', 0.5);
hold on 
plot(t_1, pos_1, 'Color', dark_orange, 'LineWidth', 0.5);
plot(min_t_1, min_pos_1,'.', 'Color', light_sea_green);%'MarkerSize', 5);
plot(t_1,fit_val_1,'Color', light_sea_green,'LineWidth', 1);
title(strcat('\fontsize{18}\rmf = ',signal_1.f_s,' rad/s; m = ', signal_1.m_s,' kg'))
xlabel('\fontsize{16}Time (s)')
ylabel('\fontsize{16}Position (cm)')
legend('Reference','Measured position','','Recovery fitting curve','Location','southeast','FontSize', 14)
grid on
xlim([0, t_1(end)])

subplot(1,2,2);
plot(t_2, ref_2, 'Color', space_cadet, 'LineWidth', 0.5);
hold on 
plot(t_2, pos_2, 'Color', dark_orange, 'LineWidth', 0.5);
plot(min_t_2, min_pos_2,'.', 'Color', light_sea_green);%'MarkerSize', 5);
plot(t_2,fit_val_2,'Color', light_sea_green,'LineWidth', 1);
title(strcat('\fontsize{18}\rmf = ',signal_2.f_s,' rad/s; m = ', signal_2.m_s,' kg'))
xlabel('\fontsize{16}Time (s)')
ylabel('\fontsize{16}Position (cm)')
legend('Reference','Measured position','','Recovery fitting curve','Location','southeast','FontSize', 14)
grid on
xlim([0, t_2(end)])

%% Export to PDF 
export = input('Export? ');
result_name = strcat(replace(signal_1.file_name, '.', ','), '_', replace(signal_2.file_name, '.', ','), 'comparison');

if export
    % Recovery
    set(rec_plot,'PaperSize',pdf_size);
    print(rec_plot, strcat(result_name, '_rec'), '-dpdf');
end