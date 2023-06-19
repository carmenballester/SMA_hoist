% Plot results with controlled positions
clear, clc, close all

% Define colors
space_cadet = [37, 37, 65]/255 * 0.5;
light_sea_green = [32, 171, 161]/255;
dark_orange = [255, 141, 26]/255;
brick_red = [206, 54, 79]/255;
ocean_blue = [73, 56, 181]/255;

colors = [brick_red; ocean_blue; dark_orange; light_sea_green];

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

freq = zeros(4,3);
load = zeros(4,4);

for i=1:4
    %% LOAD DATA
    max_time = 600;
    options = input('Options: ','s');
    signal = get_signal_data(options, max_time);

    sat = input('Saturation? ');c

    %% DEFINE VARIABLES
    % Cutdown plots
    f= str2double(signal.f_s);
    
    if sat
        num_cicles = 3;
        limit_time = round(6.2814*num_cicles/f);

        t = signal.t(1:find(signal.t==limit_time));
        pos = signal.pos(1:find(t==limit_time));
        ref = signal.ref(1:find(t==limit_time));
        c = signal.c(1:find(t==limit_time));
        int = signal.int(1:find(t==limit_time)) *5/4096;
        e = signal.e(1:find(t==limit_time));
        ep = signal.ep(1:find(t==limit_time));
    
    else
        t = signal.t;
        pos = signal.pos;
        ref = signal.ref;
        c = signal.c;
        int = signal.int;
        e = signal.e;
        ep = signal.ep;
    end

    pos_nc = signal.pos_nc;
    t_nc = signal.t_nc;

    %% PLOTS
    % Plot position -----------------------------------------------------------
    if i == 1
        pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
        control_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
        
        figure(pos_plot)
        plot(t, ref, 'LineStyle', '-', 'Color', space_cadet, 'LineWidth', 1);
        hold on 
    end

    freq(i,:) = signal.f_s;
    load(i,:) = signal.m_s;
    
    figure(pos_plot)
    plot(t, pos, 'Color', colors(i,:), 'LineWidth', 1.5);
    figure(control_plot)
    plot(t, c, 'Color', colors(i,:), 'LineWidth', 1);
    hold on

end

figure(pos_plot)
title('\bf Actuator Response','FontSize',font_size_large)
xlabel('Time (s)','FontSize',font_size_large)
ylabel('Position (cm)','FontSize',font_size_large)
legend('Reference', ...
        strcat('m = ',load(1,:),' kg'), ...
        strcat('m = ',load(2,:),' kg'), ...
        strcat('m = ',load(3,:),' kg'), ...
        strcat('m = ',load(4,:),' kg'), ...
        'Location','southeast','FontSize', font_size_small, 'NumColumns', 2);
grid on
xlim([0, t(end)])
yticklabels({'', '0', '0.5', '1', '1.5', '2', '2.5'})
set(gca,'fontsize', font_size_small) 

figure(control_plot)
title('\bf NASS Control Signal','FontSize',font_size_large)
xlabel('Time (s)','FontSize',font_size_large)
ylabel('PWM Duty Cycle (%)','FontSize',font_size_large)
legend( strcat('m = ',load(1,:),' kg'), ...
        strcat('m = ',load(2,:),' kg'), ...
        strcat('m = ',load(3,:),' kg'), ...
        strcat('m = ',load(4,:),' kg'), ...
        'Location','northeast','FontSize', font_size_small, 'NumColumns', 2);
grid on
xlim([0, t(end)])
set(gca,'fontsize', font_size_small) 

%% Export to PDF 
export = input('Export? ');
result_name = strcat(replace(signal.file_name, '.', ','), '_load_comp');

if export
    % Position
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, strcat(result_name, '_pos'), '-dpdf');

    % Control
    set(control_plot,'PaperSize',pdf_size);
    print(control_plot, strcat(result_name, '_control'), '-dpdf');
end