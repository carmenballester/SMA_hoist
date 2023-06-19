function values = recovery_mean(f_s, m_s)
    
    if strcmp(f_s,'0.4') && strcmp(m_s,'1.00')
        values.mean = 2.4; % total displacement
        values.std_mean = 0;
        values.stat = 2.4;
        values.std_stat = 0;
        values.mean_err = 2.4;
        values.mean_err_pid = 2.4;
        %values.fit.fit_eq = [];
        values.rsq = 0.0;
    else
        % LOAD DATA
        % Define paths
        folder_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
        file_name = strcat(f_s, 'f_', m_s, 'kg');
        file_path = strcat(folder_path, file_name, '.mat');
        
        % Load specifyed data
        load(file_path);
       
        % Define variables
        max_time = 600.00;
        
        t = single(POSICION.time);
        t = single(POSICION.time(1:find(t==max_time)));
        pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
        e = ERROR.signals.values(1:find(t==max_time))*0.48*10^-4;
        
        % COMPUTE RECOVERY MEAN VALUE
        % Get recovery values
        min_pos = [];
        min_pos_stat = [];
        min_t = [];
        
        f = str2double(f_s);
        T = single(round(1/f * 6.2814/2, 2));
        cicles = round((max_time/T)); 
        stab_cycles = 4;
         
        for j=1:2:cicles
            t_cicle = t(find(t==single(round(j*T,2))):find(t==single(round((j+2)*T,2))));
            p_cicle = pos(find(t==single(round(j*T,2))):find(t==single(round((j+2)*T,2))));
        
            [min_point, i] = min(p_cicle);
            min_pos = [min_pos min_point];
            min_t = [min_t t_cicle(i)];

            if j >= 2*stab_cycles
                min_pos_stat = [min_pos_stat min_point];
            end
        end

        values.mean = mean(min_pos);
        values.std_mean = std(min_pos);
        values.stat = mean(min_pos_stat);
        values.std_stat = std(min_pos_stat);
        values.mean_err = mean(abs(e));

        % Get regression fit
        start_points = [2 1];
        
        my_fit = fittype('a*atan(b*x)','dependent',{'y'},'independent',{'x'},'coefficients',{'a','b'});
        
        [fit_eq, gof] = fit(double(min_t'), double(min_pos'), my_fit, ...
            'Start', start_points, ...
            'Display', 'notify', ...
            'TolFun', 10e-10);
        %fit_val = feval(fit_eq, t);

        %values.fit.fit_eq = fit_eq;
        values.rsq = gof.rsquare;

        %% PID
        file_name = strcat(f_s, 'f_', m_s, 'kg_pid');
        file_path = strcat(folder_path, file_name, '.mat');

        if isfile(file_path)
            file_name = strcat(f_s, 'f_', m_s, 'kg_pid');
            file_path = strcat(folder_path, file_name, '.mat');
            
            % Load specified data
            load(file_path);
            
            t = single(POSICION.time);
            t = single(POSICION.time(1:find(t==max_time)));
            e = ERROR.signals.values(1:find(t==max_time))*0.48*10^-4;

            values.mean_err_pid = mean(abs(e));

        else
            values.mean_err_pid = -1;
        end
    end
end