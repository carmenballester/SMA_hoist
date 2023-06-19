function signal = get_signal_data_pid()
    % Get data parameters
    f_s = input('Frecuencia: ','s');
    m_s = input('Masa: ', 's');
    
    % Define paths
    folder_path = 'G:\Mi unidad\Research\SMA_actuator\hoist_system\hoist_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
    file_name = strcat(f_s, 'f_', m_s, 'kg');
    file_path = strcat(folder_path, file_name, '.mat');
    
    % Load specified data
    load(file_path);
    
    % Define variables
    max_time = 600.00;
    
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));
    pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
    ref = REFERENCIA.signals.values(1:find(t==max_time))*0.48*10^-4;
    c = CONTROL.signals.values(1:find(t==max_time));
    int = INTENSIDAD.signals.values(1:find(t==max_time)) *5/4096;
    e = ERROR.signals.values(1:find(t==max_time))*0.48*10^-4;
    ep = ERROR_PONDERADO.signals.values(1:find(t==max_time))*0.48*10^-4;
    
    % t = single(Posicion.time);
    % pos = Posicion.signals.values;
    % ref = referencia.signals.values(:,3);
    % c = control.signals.values(:,2);
    % ep = error_ponderado.signals.values;
    % e = ref-pos;
    
    % Get uncontrolled positions
    index = find(c == 0.0);
    pos_nc = pos(index);
    t_nc = t(index);

    % Return data
    signal.nass.f_s = f_s;
    signal.nass.m_s = m_s;
    signal.nass.file_name = file_name;
    signal.nass.t = t;
    signal.nass.pos = pos;
    signal.nass.ref = ref;
    signal.nass.c = c;
    signal.nass.int = int;
    signal.nass.e = e;
    signal.nass.ep = ep;
    signal.nass.pos_nc = pos_nc;
    signal.nass.t_nc = t_nc;

    % PID -----------------------------------------------------------------
    file_name = strcat(f_s, 'f_', m_s, 'kg_pid');
    file_path = strcat(folder_path, file_name, '.mat');
    
    % Load specified data
    load(file_path);
    
    % Define variables
    max_time = 600.00;
    
    t = single(POSICION.time);
    t = single(POSICION.time(1:find(t==max_time)));
    pos = POSICION.signals.values(1:find(t==max_time))*0.48*10^-4;
    ref = REFERENCIA.signals.values(1:find(t==max_time))*0.48*10^-4;
    c = CONTROL.signals.values(1:find(t==max_time));
    int = INTENSIDAD.signals.values(1:find(t==max_time)) *5/4096;
    e = ERROR.signals.values(1:find(t==max_time))*0.48*10^-4;
    ep = ERROR_PONDERADO.signals.values(1:find(t==max_time))*0.48*10^-4;
    
    % t = single(Posicion.time);
    % pos = Posicion.signals.values;
    % ref = referencia.signals.values(:,3);
    % c = control.signals.values(:,2);
    % ep = error_ponderado.signals.values;
    % e = ref-pos;
    
    % Get uncontrolled positions
    index = find(c == 0.0);
    pos_nc = pos(index);
    t_nc = t(index);

    % Return data
    signal.pid.f_s = f_s;
    signal.pid.m_s = m_s;
    signal.pid.file_name = file_name;
    signal.pid.t = t;
    signal.pid.pos = pos;
    signal.pid.ref = ref;
    signal.pid.c = c;
    signal.pid.int = int;
    signal.pid.e = e;
    signal.pid.ep = ep;
    signal.pid.pos_nc = pos_nc;
    signal.pid.t_nc = t_nc;
end