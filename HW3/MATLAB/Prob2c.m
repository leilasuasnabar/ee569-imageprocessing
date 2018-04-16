% 569 Homework Assignment 3
% Date: March 25th,2017
% Name: Leila Suasnabar
% ID: 3109-9816-56
% email: lsuasnabar@usc.edu
%
% Problem 3b. Run in matlab. Evaluation
clear all;clc;
%Same for all images
cols = 481;
row = 321;
params.thrs = 5;
fid = fopen('evaluation.txt','w');
fprintf(fid, '\nEVALUATION DATA\n');

%Read all the ground truths
%Boat
load('393035.mat');
gt1 = groundTruth{1};gt1.Boundaries = groundTruth{1,1}.Boundaries;
gt1.Segmentation = groundTruth{1,1}.Segmentation;
gt2 = groundTruth{2};gt2.Boundaries = groundTruth{1,2}.Boundaries;
gt2.Segmentation = groundTruth{1,2}.Segmentation;
gt3 = groundTruth{3};gt3.Boundaries = groundTruth{1,3}.Boundaries;
gt3.Segmentation = groundTruth{1,3}.Segmentation;
gt4 = groundTruth{4};gt4.Boundaries = groundTruth{1,4}.Boundaries;
gt4.Segmentation = groundTruth{1,4}.Segmentation;
gt5 = groundTruth{5};gt5.Boundaries = groundTruth{1,5}.Boundaries;
gt5.Segmentation = groundTruth{1,5}.Segmentation;
gt6 = groundTruth{6};gt6.Boundaries = groundTruth{1,6}.Boundaries;
gt6.Segmentation = groundTruth{1,6}.Segmentation;

groundTruth = num2cell(gt1); save('GT1.mat','groundTruth');
groundTruth = num2cell(gt2); save('GT2.mat','groundTruth');
groundTruth = num2cell(gt3); save('GT3.mat','groundTruth');
groundTruth = num2cell(gt4); save('GT4.mat','groundTruth');
groundTruth = num2cell(gt5); save('GT5.mat','groundTruth');
groundTruth = num2cell(gt6); save('GT6.mat','groundTruth');

input = 'BoatCanny_01_09.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%%
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatCanny_02_05.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatCanny_02_07.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatCanny_03_04.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatCanny_03_08.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatCanny_04_06.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_002.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_005.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_010.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_015.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_020.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'BoatSE_025.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);

%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

%% Repeat for castle.raw

%Read all the ground truths
%Boat
load('201080.mat');
gt1 = groundTruth{1};gt1.Boundaries = groundTruth{1,1}.Boundaries;
gt1.Segmentation = groundTruth{1,1}.Segmentation;
gt2 = groundTruth{2};gt2.Boundaries = groundTruth{1,2}.Boundaries;
gt2.Segmentation = groundTruth{1,2}.Segmentation;
gt3 = groundTruth{3};gt3.Boundaries = groundTruth{1,3}.Boundaries;
gt3.Segmentation = groundTruth{1,3}.Segmentation;
gt4 = groundTruth{4};gt4.Boundaries = groundTruth{1,4}.Boundaries;
gt4.Segmentation = groundTruth{1,4}.Segmentation;
gt5 = groundTruth{5};gt5.Boundaries = groundTruth{1,5}.Boundaries;
gt5.Segmentation = groundTruth{1,5}.Segmentation;
gt6 = groundTruth{6};gt6.Boundaries = groundTruth{1,6}.Boundaries;
gt6.Segmentation = groundTruth{1,6}.Segmentation;
groundTruth = num2cell(gt1); save('GT1.mat','groundTruth');
groundTruth = num2cell(gt2); save('GT2.mat','groundTruth');
groundTruth = num2cell(gt3); save('GT3.mat','groundTruth');
groundTruth = num2cell(gt4); save('GT4.mat','groundTruth');
groundTruth = num2cell(gt5); save('GT5.mat','groundTruth');
groundTruth = num2cell(gt6); save('GT6.mat','groundTruth');

input = 'CastleCanny_01_09.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleCanny_02_05.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleCanny_02_07.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleCanny_03_04.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleCanny_03_08.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleCanny_04_06.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_002.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_005.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_010.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_015.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_020.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

input = 'CastleSE_025.raw';
data = rawtoData(input,row,cols);
[~,cntR(1),sumR(1),cntP(1),sumP(1),~] = edgesEvalImg(data,'GT1.mat',[params]);
[~,cntR(2),sumR(2),cntP(2),sumP(2),~] = edgesEvalImg(data,'GT2.mat',[params]);
[~,cntR(3),sumR(3),cntP(3),sumP(3),~] = edgesEvalImg(data,'GT3.mat',[params]);
[~,cntR(4),sumR(4),cntP(4),sumP(4),~] = edgesEvalImg(data,'GT4.mat',[params]);
[~,cntR(5),sumR(5),cntP(5),sumP(5),~] = edgesEvalImg(data,'GT5.mat',[params]);
[~,cntR(6),sumR(6),cntP(6),sumP(6),~] = edgesEvalImg(data,'GT6.mat',[params]);
%Finding Recall and Precission
R = cntR./sumR;
P = cntP./sumP;
fprintf(fid, '\n\nFile: %s\n',input);
fprintf(fid,'\nRecall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nPrecision\n');
fprintf(fid, '%f ',P);
%Finding the mean and F-measure
cntR = sum(cntR)/6; cntP = sum(cntP)/6;
sumR = sum(sumR)/6; sumP = sum(sumP)/6;
R = cntR/sumR;
P = cntP/sumP;
F = 2*(P*R)/(R+P);
fprintf(fid,'\nMean Recall\n');
fprintf(fid, '%f ',R);
fprintf(fid,'\nMean Precision\n');
fprintf(fid, '%f ',P);
fprintf(fid,'\nF-measure\n');
fprintf(fid, '%f ',F);

