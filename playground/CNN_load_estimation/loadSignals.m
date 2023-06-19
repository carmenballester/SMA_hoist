clc, clear, close all

% CAMBIAR SEGÚN LOS ARCHIVOS QUE SE QUIERAN PROCESAR
folder_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
file_list = dir(folder_path);
file_names = {file_list.name};
f = num2str(input('Frequency?: '));
file_names = file_names(strncmp(file_names, f, 3));
file_names = file_names(~contains(file_names, 'pid') & ~contains(file_names, 'fracaso'));

image_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\GP_load_estimation\images\';
%fig = figure('Name','SMA Position','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);

t_cicle = [];
p_cicle = [];
r_cicle = [];

for i=1:length(file_names)
    file_name = cell2mat(file_names(i));
    file_path = strcat(folder_path, file_name);
    f = str2double(file_name(1:3))
    kg = str2double(file_name(6:9))

    max_time = 600;
    T = single(round(1/f * 6.2814/2, 2));
    cicles = round((max_time/T));     
    
    % Load values
    load(file_path)
    X_train = single(POSICION.time);
    X_train = single(POSICION.time(1:find(X_train==max_time)));
    p = POSICION.signals.values(1:find(X_train==max_time))*0.48*10^-4;
    r = REFERENCIA.signals.values((1:find(X_train==max_time)))*0.48*10^-4;
%     c = control.signals.values((1:find(X_train==max_time)),2);
%     int = Intensidad.signals.values(1:find(X_train==max_time)) *5/4096;
   
    fig_w = 15;
    fig_h = 15;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w fig_h];
    pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
    
    for j=1:2:cicles
        t_cicle = X_train(find(X_train==round(j*T,2)):find(X_train==round((j+2)*T,2)));
        p_cicle = p(find(X_train==round(j*T,2)):find(X_train==round((j+2)*T,2)));
        r_cicle = r(find(X_train==round(j*T,2)):find(X_train==round((j+2)*T,2)));
        
        if isempty(length(t_cicle))
            disp('empty')
        else
%             if j==1
%                 plot(t_cicle-((j-1)*T), r_cicle, '--', 'Color', [37, 37, 65]/255, 'LineWidth', 1.5);
%                  hold on 
%             end

            plot(t_cicle-((j-1)*T), p_cicle);
%             title('\bf Cooling characteristic curve', 'FontSize',20)
%             subtitle('during various cycles', 'FontSize',18)
%             xlabel('Time (s)','FontSize', 20)
%             ylabel('Position (cm)','FontSize', 20)
%             xlim([T, 3*T]);
%             xticks([T, 3*T])
%             xticklabels({'0','T'})
%             legend('Reference','Measured position','FontSize', 20, 'Location', 'northeast')
%             set(gca,'fontsize', 20) 
%             grid on
            
            set(gca,'XColor', 'none','YColor','none')
            set(gca, 'OuterPosition', [-0.16,-0.135,1.275,1.225])
         
            image_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg_', num2str(j), '.png');
            image = strcat(image_path, image_name);
            saveas(gca, image);
        end
    end

%     result_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg_cooling');
%     result_name = replace(result_name, '.', ',');
%     
%     set(pos_plot,'PaperSize',pdf_size);
%     print(pos_plot, result_name, '-dpdf');

% 
%     pause;
%     close all
end

