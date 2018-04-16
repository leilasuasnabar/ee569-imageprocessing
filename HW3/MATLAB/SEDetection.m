% 569 Homework Assignment 3
% Date: March 25th,2017
% Name: Leila Suasnabar
% ID: 3109-9816-56
% email: lsuasnabar@usc.edu
%
% Problem 2b. Run in matlab. Structured Edge Detection
%
% Source: @misc{PMT, 
%   author = {Piotr Doll\'ar}, 
%   title = {{P}iotr's {C}omputer {V}ision {M}atlab {T}oolbox ({PMT})}, 
%   howpublished = {\url{https://github.com/pdollar/toolbox}} }
% File: based on edgesDemo.m
%
%Function takes a RAW image and outputs the edges with the preset 
% threshold by using with the structured edge detector algorithm
% This algorithm is set to top accuracy
%
% Usage: [edges,E] = SEDetection(input,output,T,cols,row);
%
% Parameters:
%   input: name of input file (assumed to have 3 bytes per pixel)
%   output: name of output file
%   T: threshold
%   cols: width of image
%   row: height of image

function [edges,E] = SEDetection(input,output,T,cols,row)
%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
model.opts.multiscale=1;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=2;          % for top speed set nTreesEval=1
model.opts.nThreads=4;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms
%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end
%% read raw file
fid = fopen(input, 'r');
size = 3*row*cols;
if (fid == -1)
    error('Image cannot be opened \n');
    pause
end

%Read image
temp = fread(fid,size,'uchar');
fclose(fid);
counter = 1;
temp = uint8(temp);
%Need: I - [h x w x 3] color input image to use the edgesDetect function
I = ones(row, cols, 3);

%Passing to I
for i = 1:row
    for j = 1:cols
        I(i,j,1) = temp(counter,1);
        I(i,j,2) = temp(counter+1,1);
        I(i,j,3) = temp(counter+2,1);
        counter = counter + 3;
    end;
end;
I = uint8(I);
%% edge detection
tic, E=edgesDetect(I,model); toc
finalE = zeros(row,cols);
%Binary thresholding
for i = 1:row
    for j = 1:cols
        if (E(i, j) < T)
            finalE(i, j) = 255;
        end
    end
end
%% visualize results
fid = fopen(output,'wb');
% Check if file exists
if (fid == -1)
    error('Image cannot be opened \n');
    pause
end
% Write and close file
edges = finalE;
fwrite(fid, edges', 'uchar');
fclose(fid);

