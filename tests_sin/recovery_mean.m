function [mean_val] = recovery_mean(f_s, m_s)
    
    % LOAD DATA
    % Define paths
    folder_path = 'G:\Mi unidad\SMA Carmen\polipasto_v2\tests_sin\test_8hilos_0.31d_30cm_3vueltas_54000us_good_control\';
    file_name = strcat(f_s, 'f_', m_s, 'kg');
    file_path = strcat(folder_path, file_name, '.mat');
    
    % Load specifyed data
    load(file_path);
    
    % Define variables
    max_time = 600.00;
    
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));
    pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
    
    % COMPUTE RECOVERY MEAN VALUE
    % Get recovery values
    min_pos = [];
    
    f = str2double(f_s);
    T = single(round(1/f * 6.2814/2, 2));
    cicles = round((max_time/T)); 
     
    for j=0:2:cicles
        p_cicle = pos(find(t==round(j*T,2)):find(t==round((j+1)*T,2)));
    
        [min_point, i] = min(p_cicle);
        min_pos = [min_pos min_point];
    end
    
    mean_val = mean(min_pos);

end