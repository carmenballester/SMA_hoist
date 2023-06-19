% Plot results with controlled positions
clear, clc, close all

%% LOAD DATA
max_time = 190;
options = '_cooling';
signal = get_signal_data(options, max_time);

%% DEFINE VARIABLES
% Cutdown plots
f = str2double(signal.f_s);
T = 1/f * 6.2814/2;
sat = input('Saturation? ');

if sat
    num_cicles = 6;
    limit_time = round(6.2814*num_cicles/f);
    
    t = signal.t(1:find(signal.t==limit_time));
    pos = signal.pos(1:find(t==limit_time));
    ref = signal.ref(1:find(t==limit_time));
    c = signal.c(1:find(t==limit_time));
    int = signal.int(1:find(t==limit_time)) *5/4096;
    e = signal.e(1:find(t==limit_time));
    ep = signal.ep(1:find(t==limit_time));

    x_limits = [0, limit_time];

else
    t = signal.t;
    pos = signal.pos;
    ref = signal.ref;
    c = signal.c;
    int = signal.int;
    e = signal.e;
    ep = signal.ep;

%     x_limits = [0*T, 5*T];
    x_limits = [0, max_time];
end

pos_nc = signal.pos_nc;
t_nc = signal.t_nc;

%% PLOTS
% Define colors
light_sea_green = [32, 171, 161]/255;
space_cadet = [37, 37, 65]/255;
dark_orange = [255, 141, 26]/255;
brick_red = [206, 54, 79]/255;

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
plot(t, ref, 'Color', space_cadet, 'LineWidth', 1.5);
hold on 
plot(t, pos, 'Color', dark_orange, 'LineWidth', 1.5);
title('\bf Actuator response', 'FontSize',font_size_large)
xlabel('Time (s)','FontSize', font_size_large)
ylabel('Position (cm)','FontSize', font_size_large)

grid on
xlim(x_limits)
ylim([-0.5, 2.5])
yticklabels({'', '0', '0.5', '1', '1.5', '2', '2.5'})
set(gca,'fontsize', font_size_small) 

%% a
%% LOAD DATA
max_time = 300;
options = '';
signal = get_signal_data(options, max_time);

%% DEFINE VARIABLES
% Cutdown plots
f = str2double(signal.f_s);
T = 1/f * 6.2814/2;
sat = input('Saturation? ');

if sat
    num_cicles = 6;
    limit_time = round(6.2814*num_cicles/f);
    
    t = signal.t(1:find(signal.t==limit_time));
    pos = signal.pos(1:find(t==limit_time));
    ref = signal.ref(1:find(t==limit_time));
    c = signal.c(1:find(t==limit_time));
    int = signal.int(1:find(t==limit_time)) *5/4096;
    e = signal.e(1:find(t==limit_time));
    ep = signal.ep(1:find(t==limit_time));

    x_limits = [0, limit_time];

else
    t = signal.t;
    pos = signal.pos;
    ref = signal.ref;
    c = signal.c;
    int = signal.int;
    e = signal.e;
    ep = signal.ep;

%     x_limits = [0*T, 5*T];
    x_limits = [0, max_time];
end

pos_nc = signal.pos_nc;
t_nc = signal.t_nc;

plot(t, pos, 'Color', light_sea_green, 'LineWidth', 1.5);
legend('Reference','Forced cooling','Natural air convection','Location','southeast','FontSize', font_size_small)



%% Export to PDF 
export = input('Export? ');
result_name = replace(signal.file_name, '.', ',');

if export
    % Position
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, strcat(result_name, '_cooling'), '-dpdf');
end