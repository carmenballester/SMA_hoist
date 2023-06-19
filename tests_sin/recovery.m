% Get significant values of data and plot results
clear, clc, close all

%% LOAD DATA
signal = get_signal_data();

%% DEFINE VARIABLES
% Cutdown plots
f = str2double(signal.f_s);
T = 1/f * 6.2814/2;
sat = input('Saturation? ');

 t = signal.t;
pos = signal.pos;
ref = signal.ref;
c = signal.c;
int = signal.int;
e = signal.e;
ep = signal.ep;

if sat
    num_cicles = 8;
    limit_time = round(6.2814*num_cicles/f);
    
    x_limits = [0, limit_time];

else
    x_limits = [0, 600];
end

pos_nc = signal.pos_nc;
t_nc = signal.t_nc;

cicles = round((600/T)); 

%% COMPUTE RECOVERY FITTING
% Get recovery values
min_t = [];
min_pos = [];
 

for j=1:2:cicles
    t_cicle = t(find(t==single(round(j*T,2))):find(t==single(round((j+2)*T,2))));
    p_cicle = pos(find(t==single(round(j*T,2))):find(t==single(round((j+2)*T,2))));
    r_cicle = ref(find(t==single(round(j*T,2))):find(t==single(round((j+2)*T,2))));


%     t_cicle = t(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));
%     p_cicle = pos(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));
%     r_cicle = ref(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));

    [min_point, i] = min(p_cicle);
    min_pos = [min_pos min_point];
    min_t = [min_t t_cicle(i)];
end

% Get regression fit
start_points = [2 1];

my_fit = fittype('a*atan(b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});
%my_fit = fittype('a*x^b+c','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b','c'});
  

[fit_eq, gof] = fit(double(min_t'), double(min_pos'), my_fit, ...
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
plot(t, ref, 'Color', space_cadet, 'LineWidth', 0.5);
hold on 
plot(t, pos, 'Color', dark_orange, 'LineWidth', 0.5);
plot(min_t, min_pos, '.', 'Color', light_sea_green);%'MarkerSize', 5);
title('\bf SMA Response', 'FontSize',font_size_large)
xlabel('Time (s)','FontSize',font_size_large)
ylabel('Position (cm)','FontSize',font_size_large)
legend('Reference','Measured position','Recovery fitting curve','Location','southeast','FontSize',font_size_small)
grid on
xlim(x_limits)
set(gca,'fontsize', font_size_small) 

% Plot recovery curve
rec_plot = figure('Name','SMA Recovery Curve','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
plot(t, ref, 'Color', space_cadet, 'LineWidth', 1);
hold on 
plot(t, pos, 'Color', dark_orange, 'LineWidth', 1);
plot(min_t, min_pos,'.', 'Color', light_sea_green,'MarkerSize', 10);
plot(t,fit_val,'Color', light_sea_green,'LineWidth', 1);
title('SMA Recovery Curve','FontSize',font_size_large)
xlabel('Time (s)','FontSize',font_size_large)
ylabel('Position (cm)','FontSize',font_size_large)
legend('Reference','Measured position','','Recovery fitting curve','Location','northeast','FontSize',font_size_small)
grid on
xlim(x_limits)
ylim([0,2.5])
%yticklabels({'', '0', '0.5', '1', '1.5', '2', '2.5'})
set(gca,'fontsize', font_size_small) 

%% Export to PDF 
export = input('Export? ');
result_name = replace(signal.file_name, '.', ',');

if export
%     % Position
%     set(pos_plot,'PaperSize',pdf_size);
%     print(pos_plot, strcat(result_name, '_pos_rec'), '-dpdf');
    
    % Recovery
    set(rec_plot,'PaperSize',pdf_size);
    print(rec_plot, strcat(result_name, '_rec'), '-dpdf');
end