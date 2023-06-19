clc, clear, close all

% Load and process data
train_info = readtable("train_info_CNN_best.csv");

% confusion_matrix = [589 81 43 0; 0 1163 33 0; 0 7 1172 73; 16 43 0 1208];
% confusion_matrix = [20 0 0 0; 5 25 0 0; 0 0 30 0; 5 0 5 25];

confusion_matrix = [15 5 0 0; 0 20 0 0; 0 0 40 0; 0 0 0 35];

window_size = 3;
val_loss_med = medfilt1(train_info.val_loss, window_size);
val_acc_med = medfilt1(train_info.val_acc, window_size);

%% Plots
% Define colors
uranian_blue = [167,208,241]/255;
air_superiority_blue = [96,150,186]/255;

salmon_pink = [243, 181, 199]/255;
cerise = [209, 77, 99]/255;

% Define figure properties
h = input('Square (0) or Rectangle (1)?: ');

if h
    fig_w = 40;
    fig_h = 17;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w-6 fig_h];
    font_size_small = 20;
    font_size_large = 25;
else
    fig_w = 20;
    fig_h = 15;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w fig_h];
    font_size_small = 20;
    font_size_large = 25;
end

% Plot confusion matrix
confusion_matrix_plot = figure('Name','Confusion Matrix','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
labels = ['1.0'; '1.5'; '2.0'; '2.5'];
confusionchart(confusion_matrix, labels)
xlabel('Predicted load (kg)')
ylabel(['True load (kg)'])
set(gca,'fontsize', font_size_small)

% Plot position
loss_accuracy_plot = figure('Name','LOSS','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
subplot(1,2,1)
plot(train_info.train_loss, 'Color', uranian_blue, 'LineWidth', 1);
hold on 
plot(val_loss_med, 'Color',air_superiority_blue, 'LineWidth', 1.5);
title('\bf Loss','FontSize',font_size_large)
xlabel('Step','FontSize',font_size_large)
%ylabel('loss & accuracy','FontSize',font_size_large)
legend('Training','Validation','Training','Validation','Location','northeast','FontSize', font_size_small)
grid on
set(gca,'fontsize', font_size_small)

% Plot accuracy
% accuracy_plot = figure('Name','LOSS','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
subplot(1,2,2)
plot(train_info.train_acc, 'Color', salmon_pink, 'LineWidth', 1);
hold on 
plot(val_acc_med, 'Color', cerise, 'LineWidth', 1.5);
title('\bf Accuracy','FontSize',font_size_large)
xlabel('Step','FontSize',font_size_large)
%ylabel('Loss','FontSize',font_size_large)
legend('Training','Validation','Location','southeast','FontSize', font_size_small)
grid on
set(gca,'fontsize', font_size_small)


%% Export to PDF 
export = input('Export? ');
result_name = 'transformer_load_est';

if export && h
    % Loss & accuracy
    set(loss_accuracy_plot,'PaperSize',pdf_size);
    print(loss_accuracy_plot, strcat(result_name, '_loss_acc'), '-dpdf');

elseif export &&  ~h
     % Confussion matrix
    set(confusion_matrix_plot,'PaperSize',pdf_size);
    print(confusion_matrix_plot, strcat(result_name, '_conf_mat'), '-dpdf');    

end