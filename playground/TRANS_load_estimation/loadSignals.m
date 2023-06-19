clc%, clear, close all

% figure

% f1 = figure('Name','1kg');
% f2 = figure('Name','1.5kg');
% f3 = figure('Name','2kg');
% f4 = figure('Name','2.5kg');

% CAMBIAR SEGÚN LOS ARCHIVOS QUE SE QUIERAN PROCESAR
folder_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
file_list = dir(folder_path);
file_names = {file_list.name};
f = num2str(input('Frequency?: '));
file_names = file_names(strncmp(file_names, f, 3));
file_names = file_names(~contains(file_names, 'pid') & ~contains(file_names, 'fracaso') & ~contains(file_names, 'cooling'));

t_cicle = [];
p_cicle = [];
r_cicle = [];

for i=1:length(file_names)
    file_name = cell2mat(file_names(i));
    file_path = strcat(folder_path, file_name);
    f = str2double(file_name(1:3));
    kg = str2double(file_name(6:9));

    max_time = 600;
    sample_time = 0.01;
    
    T = single(round(1/f * 6.2814/2, 2));
    cicles = round((max_time/T));
    N_o = double(2*T/sample_time + 1);
    N_r = 128;

    %% Load values
    load(file_path)
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));

    % centimeters
%     r = REFERENCIA.signals.values(1:find(t==max_time))*0.48*10^-4; % cm
%     p = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4; % cm
%     e = ERROR.signals.values(1:find(t==max_time))*0.48*10^-4; % cm;

    % sensor units
    r = round(REFERENCIA.signals.values(1:find(t==max_time)));
    p = POSICION.signals.values(1:find(t==max_time));
    e = round(ERROR.signals.values(1:find(t==max_time)));
    c = round(CONTROL.signals.values(1:find(t==max_time)));

    %% Get cicle
    fig_w = 15;
    fig_h = 15;
    fig_pos = [0 0 fig_w fig_h];
    pdf_size = [fig_w fig_h];

%     pos_plot = figure('Name','SMA Position Control','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position', fig_pos);
    
    for j=1:2:cicles
        t_cicle = t(find(t==round(j*T,2)):find(t==round((j+2)*T,2)));
        p_cicle = p(find(t==round(j*T,2)):find(t==round((j+2)*T,2)));
        r_cicle = r(find(t==round(j*T,2)):find(t==round((j+2)*T,2)));
        e_cicle = e(find(t==round(j*T,2)):find(t==round((j+2)*T,2)));
        c_cicle = c(find(t==round(j*T,2)):find(t==round((j+2)*T,2)));
        
        if isempty(p_cicle)
%             disp('empty')
        
        % RESAMPLE
        else
            t_cicle = t_cicle';
            t_res = linspace(t_cicle(1), t_cicle(end), N_r)';

            res = [];
            for i=1:length(t_res)
                index = find(t_cicle == round(t_res(i),2));
                res = [res index];
            end

            p_res = p_cicle(res);
            r_res = r_cicle(res);
            e_res = e_cicle(res);
            c_res = c_cicle(res);
%             length(p_res)
%             plot(p_res)     
        end
%         pause;

        
        % Rescale data
%         data = rescale(p_res, 0, 1);

        data = c_res;

%         % Plot
%         hold on
%         plot(data)
%         if kg == 1.0
%             figure(f1);
%             plot(data);
%         elseif kg == 1.5
%             figure(f2);
%             plot(data);
%         elseif kg == 2.0
%             figure(f3);
%             plot(data)
%         elseif kg == 2.5
%             figure(f4); 
%             plot(data);
%         end
        
        % Save single csv
        data_table = array2table(data);
        data_table.Properties.VariableNames(1) = {'control'};
        
        result_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\TRANS_load_estimation\data_control\';
        label_folder = strcat(num2str(kg*1000), '\');
    
        result_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg_', num2str(j));
        result_name = replace(result_name, '.', ',');
    
        data_path = strcat(result_path,label_folder,result_name);
    
        writetable(data_table, strcat(data_path, '.csv'))
    
%         %% Save complete csv
%         data = [r,p,e];
%         
%         data_table = array2table(data);
%         data_table.Properties.VariableNames(1:3) = {'reference','position','error'};
%         
%         result_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\TRANS_load_estimation\data_norm\';
%         label_folder = strcat(num2str(kg*1000), '\');
%     
%         result_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg');
%         result_name = replace(result_name, '.', ',');
%     
%         data_path = strcat(result_path,label_folder,result_name);
%     
%         writetable(data_table, strcat(data_path, '.csv'))
    end
end

