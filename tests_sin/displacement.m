% Probando cosas
clear, clc, close all

% Define colors
space_cadet = [37, 37, 65]/255 ;
light_sea_green = [32, 171, 161]/255;
bisque = [255, 225, 194]/255;
dark_orange = [255, 141, 26]/255;
brick_red = [206, 54, 79]/255;
ocean_blue = [73, 56, 181]/255;

% Define physic variables
N = 1:1:5; % Numero de vueltas del polipasto
l = 0:10:100; % cm de longitud del hilo
n = 3; % My number of turns

s = zeros(length(N), length(l)); % Displacement
R = zeros(length(N));

% Define graphic variables
color_plot_s = zeros(length(N)+2, 3);
color_plot_b = zeros(length(N), 3);

%% GET DATA
% Displacement
for i=1:length(N) 
    s(i,:) = 0.03*i*l;
    if i == 1
        color_plot_s(i,:) = light_sea_green(1,:);
    elseif i == n
        color_plot_s(i,:) = dark_orange(1,:);
    else
        color_plot_s(i,:) = bisque(1,:);
    end
end
color_plot_s(length(N)+1:length(N)+2, :) = [space_cadet(1,:); space_cadet(1,:)];

% Relation R
for i=1:length(N) 
    R(i,i) = 0.03*i*100;
    if i == 1
        color_plot_b(i,:) = light_sea_green(1,:);
    elseif i == n
        color_plot_b(i,:) = dark_orange(1,:);
    else
        color_plot_b(i,:) = bisque(1,:);
    end
end

% Displacement points
a = find(s(1,:) == 3);
b = interp1(s(3,:),l,3);

xp = [b, b, l(1,a)];
yp = [0, s(1,a), s(1,a)];

strp = {[], ['l = 33.3'], ['l = 100']};
%% PLOTS 
fig_w = 20;
fig_h = 30;
fig_pos = [0 0 fig_w fig_h];
pdf_size = [fig_w fig_h-8];

% Displacement lineal
disp_plot = figure('Name','Parallel Hoist SMA Actuator Displacement','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
%sgtitle('\fontsize{30} \bf Displacement improvement using hoist system')

plot(l,s,'LineWidth',2)
hold on 
plot(xp, yp, '--', 'LineWidth',2)
plot(xp(2:end), yp(2:end), '.', MarkerSize=20)
text(xp-20, yp+0.5, strp, 'FontSize', 25, 'FontName', 'Times New Roman')
% text(xp(2)-11, yp(2)+0.75, strp(2))
colororder(color_plot_s)
xlabel('\fontsize{30}SMA wire length (cm)')
ylabel('\fontsize{30}Displacement (cm)')
yticks([0 3 6 9 12 15])
ylim([0,16])
legend('Single SMA Actuator','', ...
       'Parallel Hoist SMA Actuator (3 turns)', ...
       'Parallel Hoist SMA Actuator (n turns)', ...
       'Location','northwest', ...
       'FontSize', 20)
grid on
set(gca,'fontsize', 25) 

% Displacement bar
bar_plot = figure('Name','Parallel Hoist SMA Actuator Displacement','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
%sgtitle('\fontsize{30} \bf Displacement improvement using hoist system')

b = barh(N,R,0.6,'stacked');
for i=1:length(N)
    b(i).FaceColor =  color_plot_b(i,:);
end
ylabel('\fontsize{30}Number of hoist turns')
xlabel('\fontsize{30}Displacement over total lenght (%)')
xticks([0 3 6 9 12 15])
xlim([0,16])
ylim([0,7])
legend({'Single SMA Actuator','', ...
       'Parallel Hoist SMA Actuator (3 turns)', ...
       'Parallel Hoist SMA Actuator (n turns)'}, ...
       'Location','northwest', ...
       'FontSize', 20)
grid on
set(gca,'fontsize', 25) 

%% Export to PDF 
export = input('Export? ');
result_name = 'displacement_comp';

if export
    set(disp_plot,'PaperSize',pdf_size);
    print(disp_plot, result_name, '-dpdf');

    set(bar_plot,'PaperSize',pdf_size);
    print(bar_plot, strcat(result_name, '_bar'), '-dpdf');
    
end