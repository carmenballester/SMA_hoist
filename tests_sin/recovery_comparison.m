clc, clear, close all

% Define colors
skoleboff = [25, 114, 120]/255;
morning_blue = [131, 168, 166]/255;

new_york_pink = [217, 145, 133]/255;
international_orange_golden = [196, 69, 54]/255;

maximum_green = [111, 148, 76]/255;
dark_sea_green = [160, 185, 141]/255;

% Define variables
f = ['0.3'; '0.5'; '0.7'];
m = ['0.50'; '0.75'; '1.00'; '1.25'; '1.50'; '1.75'; '2.00'];
percent_values = zeros(length(f), length(m));
mean_values = zeros(length(f), length(m));


%% COMPUTE RECOVERY MEAN
total_displacement = 2.592;

for i=1:length(f)
    for j=1:length(m)
        percent_values(i,j) = (total_displacement-recovery_mean(f(i,:), m(j,:)))*100/total_displacement;
    end
end

% Define table
% colnames = {'0.50', '0.75', '1.00', '1.25', '1.50', '1.75', '2.00'};
% rownames = {'0.3', '0.5', '0.7'};
% mean_table = array2table(mean_values);
% mean_table.Properties.VariableNames = colnames;
% mean_table.Properties.RowNames = rownames;

%% PLOTS
fig_w = 25;
fig_h = 13;
fig_pos = [10 5 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

% Plot graphic
pos_plot = figure('Name','SMA Recovery Comparison','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
% Plot lines
m_num = [0.50; 0.75; 1.00; 1.25; 1.50; 1.75; 2.00];
plot(m_num, percent_values(1,:), '--', 'LineWidth', 2, 'Color', morning_blue);
hold on
plot(m_num, percent_values(2,:), '--', 'LineWidth', 2, 'Color', new_york_pink);
plot(m_num, percent_values(3,:), '--', 'LineWidth', 2, 'Color', dark_sea_green);
% Plot points
plot(m_num, percent_values(1,:), '.', 'MarkerSize', 25, 'Color', skoleboff);
plot(m_num, percent_values(2,:), '.', 'MarkerSize', 25, 'Color', international_orange_golden);
plot(m_num, percent_values(3,:), '.', 'MarkerSize', 25, 'Color', maximum_green);
% Plot data label
% WIP
% Settings
title('\fontsize{18} \bf SMA Recovery')
xlabel('\fontsize{16}Load (kg)')
xticks(m_num)
ylabel('\fontsize{16}Recovered Position (%)')
ylim([0 100])
grid on
legend(...
    'f = 0.3 rad/s',...
    'f = 0.5 rad/s',...
    'f = 0.7 rad/s',...
    'Location','southeast')

pause;
%% Export to PDF 
export = input('Export? ');
result_name = 'recovery_comparison';

if export 
    % Recovery
    set(pos_plot,'PaperSize',pdf_size);
    print(pos_plot, result_name, '-dpdf');
end



