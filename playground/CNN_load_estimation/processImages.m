clc, clear, close all

% CAMBIAR SEGÚN LOS ARCHIVOS QUE SE QUIERAN PROCESAR
folder_path = 'images\';
file_list = dir(folder_path);
file_names = {file_list.name};
file_names = file_names(strncmp(file_names, '0.', 2));

% image_path = 'images_resized\';
image_path = 'images_resized_BNN\';
fig = figure('Name','SMA Position','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);

for i=1:length(file_names)
    file_name = cell2mat(file_names(i));
    file_path = strcat(folder_path, file_name);
    load = num2str(str2double(file_name(6:9))*100);
    freq = str2double(file_name(1:3));
    
    % Load values
    image = imread(file_path);
    image_rz = imresize(rgb2gray(image), [256, 256]);
    imshow(image_rz);

%     % Save in common folder
%     image_name = strcat(file_name(1:length(file_name)-4), '.png');
% %     image = strcat(image_path, load, '\', image_name);
%     image = strcat(image_path, image_name);
%     imwrite(image_rz, image);

    if freq ~= 0.4 
        % Save in specific folder
        image_name = strcat(file_name(1:length(file_name)-4), '.png');
        image_path = strcat('images_resized\', load, '\');
        image = strcat(image_path, image_name);
        imwrite(image_rz, image);
    end

end