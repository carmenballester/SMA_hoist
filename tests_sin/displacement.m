% Probando cosas
clear, clc, close all

% Define colors
outer_space_crayola = [40, 61, 59]/255;
skoleboff = [25, 114, 120]/255;
morning_blue = [131, 168, 166]/255;
champagne_pink = [237, 221, 212]/255;
new_york_pink = [217, 145, 133]/255;
international_orange_golden = [196, 69, 54]/255;
liver_organ = [119, 46, 37]/255;

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
        color_plot_s(i,:) = skoleboff(1,:);
    elseif i == n
        color_plot_s(i,:) = international_orange_golden(1,:);
    else
        color_plot_s(i,:) = champagne_pink(1,:);
    end
end
color_plot_s(length(N)+1:length(N)+2, :) = [outer_space_crayola(1,:); outer_space_crayola(1,:)];

% Relation R
for i=1:length(N) 
    R(i,i) = 0.03*i*100;
    if i == 1
        color_plot_b(i,:) = morning_blue(1,:);
    elseif i == n
        color_plot_b(i,:) = new_york_pink(1,:);
    else
        color_plot_b(i,:) = champagne_pink(1,:);
    end
end

% Displacement points
a = find(s(1,:) == 3);
b = interp1(s(3,:),l,3);

xp = [b, l(1,a)];
yp = [3, s(1,a)];

strp = {['L = 33.3' newline 's = 3'], ['L = 100' newline 's = 3']};
%% PLOTS 
fig_w = 37.5;
fig_h = 19.5;
fig_pos = [0 0 fig_w fig_h];
pdf_size = [fig_w+0.25 fig_h+0.25];

disp_plot = figure('Name','Parallel Hoist SMA Actuator Displacement','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
sgtitle('\fontsize{18} \bf Displacement improvement using hoist system')

% Displacement lineal
subplot(1,2,2)
plot(l,s)
hold on 
plot(xp, yp, '--')
plot(xp, yp, '.', MarkerSize=20)
text(xp-11, yp+0.75, strp)
% text(xp(2)-11, yp(2)+0.75, strp(2))
colororder(color_plot_s)
xlabel('\fontsize{16}SMA wire length')
ylabel('\fontsize{16}Displacement (cm)')
legend('Single SMA Actuator','', ...
       'Parallel Hoist SMA Actuator (3 turns)', ...
       'Parallel Hoist SMA Actuator (n turns)', ...
       'Location','northwest')
grid off
% xlim([1, l(end)])

% Displacement bar
subplot(1,2,1)
b = bar(N,R,0.6,'stacked');
for i=1:length(N)
    b(i).FaceColor =  color_plot_b(i,:);
end
xlabel('\fontsize{16}Number of hoist turns')
ylabel('\fontsize{16}Displacement over total lenght (%)')
legend({'Single SMA Actuator','', ...
       'Parallel Hoist SMA Actuator (3 turns)', ...
       'Parallel Hoist SMA Actuator (n turns)'}, ...
       'Location','northwest')
grid off

%% Export to PDF 
export = input('Export? ');
result_name = 'displacement_comparison';

if export
    set(disp_plot,'PaperSize',pdf_size);
    print(disp_plot, result_name, '-dpdf');
    
end