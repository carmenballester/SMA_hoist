clc, clear, close all

%% Load data
ds_path = 'images_resized\';

ds_images = imageDatastore(ds_path, ...
    'IncludeSubfolders', true, ...
    'LabelSource','foldernames');

% Set train and test sets
num_samples = countcats(ds_images.Labels);
[train_images, val_images, test_images] = splitEachLabel(ds_images, 0.7, 0.15, 'randomize');

%% Define network architecture

input_size = [255 255 1];
num_classes = length(unique(ds_images.Labels));

layers = [
    imageInputLayer(input_size)
    
    convolution2dLayer(3,8,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    maxPooling2dLayer(2,'Stride',2)
    
    convolution2dLayer(3,16,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    maxPooling2dLayer(2,'Stride',2)

    convolution2dLayer(3,32,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    maxPooling2dLayer(2,'Stride',2)
    
    convolution2dLayer(3,64,'Padding','same')
    batchNormalizationLayer
    reluLayer
    
    maxPooling2dLayer(2,'Stride',2)
    
    convolution2dLayer(3,128,'Padding','same')
    batchNormalizationLayer
    reluLayer

    fullyConnectedLayer(num_classes)
    softmaxLayer
    classificationLayer];
%     regressionLayer];

%% Train NN
options = trainingOptions('sgdm', ...
    'MaxEpochs', 500, ...
    'ValidationData', val_images, ...
    'ValidationFrequency',5, ...
    'Verbose',false, ...
    'Plots','training-progress');

net = trainNetwork(train_images, layers, options);

%% Test NN
clc, close all
load_pred = classify(net, test_images);
load_real = test_images.Labels;

%load_pred = categorical(str2double(char(load_pred))/100);
%load_real = categorical(str2double(char(load_real))/100);

fig = figure('Name','Confusion Matrix','NumberTitle','off', 'Color', 'white', 'Units','centimeters', 'Position',[10 5 16 13]);
confusion_mat = confusionmat(load_pred, load_real);

confusionchart(load_real, load_pred);

accuracy = mean(load_pred == load_real)
