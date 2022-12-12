function signal = get_signal_data()
    % Get data parameters
    f_s = input('Frecuencia: ','s');
    m_s = input('Masa: ', 's');
    
    % Define paths
    folder_path = 'G:\Mi unidad\SMA Carmen\polipasto_v2\tests_sin\data\test_8hilos_0.38d_30cm_3vueltas_50000us\';
    
    pid = input('PID? ');
    if pid
        file_name = strcat(f_s, 'f_', m_s, 'kg_pid');
    else
        file_name = strcat(f_s, 'f_', m_s, 'kg');
    end

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
    e = ERROR.signals.values(1:find(t==max_time));
    ep = ERROR_PONDERADO.signals.values(1:find(t==max_time));
    
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
    signal.f_s = f_s;
    signal.m_s = m_s;
    signal.file_name = file_name;
    signal.t = t;
    signal.pos = pos;
    signal.ref = ref;
    signal.c = c;
    signal.int = int;
    signal.e = e;
    signal.ep = ep;
    signal.pos_nc = pos_nc;
    signal.t_nc = t_nc;
end