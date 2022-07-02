% Get significant values of data and plot results
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
skoleboff = [25, 114, 120]/255;
fuzzy_wuzzy = [211, 106, 95]/255;
unbleached_silk = [255, 212, 202]/255;
charcoal = [38 70 83]/255;
% persian_green = [42 157 143]/255;
% maize_crayola = [233 196 106]/255;
% sandy_brown = [244 162 97]/255;
% burnt_sienna = [231 111 81]/255;

% Define saturation
sat = input('Saturation? ');
max_time = 600.00;
f = str2double(f_s);
% num_ciclos = 10;
% max_time = round(6.2814*num_ciclos/f);

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

%% COMPUTE RECOVERY FITTING
% Get recovery values
min_t = [];
min_pos = [];

T = single(round(1/f * 6.2814/2, 2));
cicles = round((max_time/T)); 
 
for j=0:2:cicles
    t_cicle = t(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));
    p_cicle = pos(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));
    r_cicle = ref(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));

    [min_point, i] = min(p_cicle);
    min_pos = [min_pos min_point];
    min_t = [min_t t_cicle(i)];
end

% Get regression fit
start_points = [1 0.5];

my_fit = fittype('a*atan(b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});

fit_eq = fit(double(min_t'), double(min_pos'), my_fit, ...
    'Start', start_points, ...
    'Display', 'notify', ...
    'TolFun', 10e-10);
fit_val = feval(fit_eq, t);

% For comparison
% log_fit2 = fittype('a-exp(-b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});
% f2 = fit(double(min_t'),double(min_pos'),log_fit2, ...
%     'Start', start_points, ...
%     'Display', 'iter', ...
%     'TolFun', 10e-10);

%% PLOTS
fig_pos = [10 5 16 13];
pdf_size = [17 14];

% Plot position
pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, '--', 'Color', unbleached_silk, 'LineWidth', 0.5);
hold on 
plot(t, pos, 'Color', fuzzy_wuzzy, 'LineWidth', 0.5);
plot(min_t, min_pos,'.', 'Color', skoleboff);%'MarkerSize', 5);
title('\fontsize{18} \bf SMA Position')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Recovery fitting curve','Location','southeast')
grid on
xlim([0, t(end)])

% Plot recovery curve
rec_plot = figure('Name','SMA Recovery Curve','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, '--', 'Color', unbleached_silk, 'LineWidth', 0.5);
hold on 
plot(t, pos, 'Color', fuzzy_wuzzy, 'LineWidth', 0.5);
plot(min_t, min_pos,'.', 'Color', skoleboff);%'MarkerSize', 5);
plot(t,fit_val,'Color', skoleboff);
title('\fontsize{18} \bf SMA Recovery Curve')
xlabel('\fontsize{16}Time')
ylabel('\fontsize{16}cm')
legend('Reference','Measured position','Recovery fitting curve','Location','southeast')
grid on
xlim([0, t(end)])

%% Export to PDF 
export = input('Export? ');
result_name = replace(file_name, '.', ',');

if export
    % Position
    set(pos_plot,'PaperSize',[17 14]);
    print(pos_plot, strcat(result_name, '_pos_rec'), '-dpdf');
    
    % Recovery
    set(rec_plot,'PaperSize',[17 14]);
    print(rec_plot, strcat(result_name, '_rec'), '-dpdf');
end