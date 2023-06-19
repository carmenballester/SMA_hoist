clc, clear, close all

% Define variables
f = ['0.1'; '0.2'; '0.3'; '0.4'];
m = ['1.00'; '1.50'; '2.00'; '2.50'];
percent_mean_values = zeros(length(f), length(m));
percent_stat_values = zeros(length(f), length(m));
mean_values = zeros(length(f), length(m));
mean_std = zeros(length(f), length(m));
stat_values = zeros(length(f), length(m));
stat_std = zeros(length(f), length(m));
disp_mean_values = zeros(length(f), length(m));
disp_stat_values = zeros(length(f), length(m));
error_values = zeros(length(f), length(m));
error_values_pid = zeros(length(f), length(m));

fit_rsq = zeros(length(f), length(m));

%% COMPUTE RECOVERY MEAN
total_displacement = 2.4; %cm
% minimum_displacement = 0.891;
minimum_displacement = 33.33;

for i=1:length(f)
    for j=1:length(m)
        values = recovery_mean(f(i,:), m(j,:));
        mean_values(i,j) = values.mean;
        stat_values(i,j) = values.stat;
        percent_mean_values(i,j) = round((total_displacement-mean_values(i,j))*100/total_displacement, 2);
        mean_std(i,j) = round(values.std_mean*100/total_displacement, 2);
        percent_stat_values(i,j) = round((total_displacement-stat_values(i,j))*100/total_displacement, 2);
        stat_std(i,j) = round(values.std_stat*100/total_displacement, 2);


        disp_mean_values(i,j) = total_displacement - mean_values(i,j);
        disp_stat_values(i,j) = total_displacement - stat_values(i,j);

        error_values(i,j) = values.mean_err;
        error_values_pid(i,j) = values.mean_err_pid;

        fit_rsq(i,j) = values.rsq;
    end
end

%% PLOTS
% % Define colors
% space_cadet = [37, 37, 65]/255 * 0.5;
% light_sea_green = [32, 171, 161]/255;
% dark_orange = [255, 141, 26]/255;
% brick_red = [206, 54, 79]/255;
% ocean_blue = [73, 56, 181]/255;
% 
% % Define figure properties
% fig_w = 25;
% fig_h = 13;
% fig_pos = [10 5 fig_w fig_h];
% pdf_size = [fig_w+0.25 fig_h+0.25];
% 
% % Plot graphic
% pos_plot = figure('Name','SMA Recovery Comparison','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% % Plot lines
% m_num = [1.00; 1.50; 2.00; 2.50];
% plot(m_num, percent_values(1,:), '--', 'LineWidth', 2, 'Color', brick_red);
% hold on
% plot(m_num, percent_values(2,:), '--', 'LineWidth', 2, 'Color', ocean_blue);
% plot(m_num, percent_values(3,:), '--', 'LineWidth', 2, 'Color', dark_orange);
% plot(m_num, percent_values(4,:), '--', 'LineWidth', 2, 'Color', light_sea_green);
% % Plot points
% plot(m_num, percent_values(1,:), '.', 'MarkerSize', 25, 'Color', brick_red);
% plot(m_num, percent_values(2,:), '.', 'MarkerSize', 25, 'Color', ocean_blue);
% plot(m_num, percent_values(3,:), '.', 'MarkerSize', 25, 'Color', dark_orange);
% plot(m_num, percent_values(4,:), '.', 'MarkerSize', 25, 'Color', light_sea_green);
% % Plot data label
% % WIP
% % Settings
% title('\fontsize{18} \bf SMA Recovery')
% xlabel('\fontsize{16}Load (kg)')
% xticks(m_num)
% ylabel('\fontsize{16}Recovered Position (%)')
% ylim([0 100])
% grid on
% legend(...
%     'f = 0.1 rad/s',...
%     'f = 0.2 rad/s',...
%     'f = 0.3 rad/s',...
%     'f = 0.4 rad/s',...
%     'Location','southeast')
%% BAR PLOT
% Define colors
soft_red = [221,155,155]/255;
soft_blue = [174,205,210]/255;
soft_yellow = [250,223,127]/255;
soft_green = [219,232,193]/255;
space_cadet = [37, 37, 65]/255;

colors = [soft_blue; soft_green; soft_yellow; soft_red];

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

%x = 0.1:0.1:0.4;
x = [0.1, 0.2, 0.3, 0.4];
b = bar(percent_stat_values);
for i=1:length(x)
    b(i).FaceColor = colors(i,:);
%     b(i).BarWidth = 0.25;
end

hold on
%yline(total_displacement,'k--','Maximum displacement', 'FontSize', font_size_small, 'LineWidth',1, 'Color', space_cadet)
yline(minimum_displacement,'k--',['Single actuator' newline 'displacement'], 'FontSize', font_size_small, 'LineWidth',1, 'Color', space_cadet)

title('\bf Actuator nominal displacement respect maximum displacement', 'FontSize',font_size_large)
xlabel('Frequency (rad/s)','FontSize', font_size_large)
ylabel('Displacement (%)','FontSize', font_size_large)

%ylim([0,2.6])
%y_ticks = [0, 0.5, minimum_displacement, 1, 1.5, 2, total_displacement, 2.5];
set(gca,'xticklabel', x);
%set(gca,'YTick', y_ticks);
set(gca,'fontsize', font_size_small) 
legend( strcat('m = 1.00 kg'), ...
        strcat('m = 1.50 kg'), ...
        strcat('m = 2.00 kg'), ...
        strcat('m = 2.50 kg'), ...
        'Location','northeast','FontSize', font_size_small);
grid on




%% Export to PDF 
export = input('Export? ');
result_name = 'recovery_comparison';

if export 
    % Recovery
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, result_name, '-dpdf');
end 
