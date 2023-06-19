clc, clear, close all

% CAMBIAR SEGÚN LOS ARCHIVOS QUE SE QUIERAN PROCESAR
folder_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
file_list = dir(folder_path);
file_names = {file_list.name};
f = num2str(input('Frequency?: '));
file_names = file_names(strncmp(file_names, f, 3));
file_names = file_names(~contains(file_names, 'pid') & ~contains(file_names, 'fracaso') & ~contains(file_names, 'cooling'));

for i=1:length(file_names)
    file_name = cell2mat(file_names(i));
    file_path = strcat(folder_path, file_name);
    f = str2double(file_name(1:3));
    kg = str2double(file_name(6:9));

    max_time = 600;

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

    data = downsample(p,10);
    
    data_table = array2table(data);
    data_table.Properties.VariableNames(1) = {'position'};
    
    result_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\TRANS_load_estimation\data_seq\';
    label_folder = strcat(num2str(kg*1000), '\');

    result_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg');
    result_name = replace(result_name, '.', ',');

    data_path = strcat(result_path,label_folder,result_name);

    writetable(data_table, strcat(data_path, '.csv'))

        %% Save complete csv
        data = [r,p,e];
        
        data_table = array2table(data);
        data_table.Properties.VariableNames(1:3) = {'reference','position','error'};
        
        result_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\TRANS_load_estimation\data_seq\';
        label_folder = strcat(num2str(kg*1000), '\');
    
        result_name = strcat(num2str(f), 'f_', num2str(kg,'%.2f'), 'kg');
        result_name = replace(result_name, '.', ',');
    
        data_path = strcat(result_path,label_folder,result_name);
    
        writetable(data_table, strcat(data_path, '.csv'))
end

