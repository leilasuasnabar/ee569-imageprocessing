% 569 Homework Assignment 3
% Date: March 25th,2017
% Name: Leila Suasnabar
% ID: 3109-9816-56
% email: lsuasnabar@usc.edu
%
% Problem 3a. Run in matlab. 
% Code based on http://www.vlfeat.org/overview/sift.html
%
clc;clear all;

%% Part a - Extraction and Description of Salient Points
row = 500;
cols = 300;
bytes = 3;

% SIFT
%Find points of interest from suv.raw
input = 'suv.raw';

[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
figure(1)
imshow(I)

% Set parameters
peak_threshold = 8; edge_threshold = 100;
[f,d] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

h = vl_plotframe(f);
set(h,'color','g','linewidth',2);
title('SIFT - points of interest');

%Find points of interest from truck.raw
input = 'truck.raw';

[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
figure(2)
imshow(I)

% Set parameters 
peak_threshold = 10; edge_threshold = 100;
[f,d] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

h = vl_plotframe(f);
set(h,'color','g','linewidth',2);
title('SIFT - points of interest');

% SURF
%Find points of interest from suv.raw
input = 'suv.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
figure(3)
Igray = uint8(Igray);
imshow(I); hold on;
points = detectSURFFeatures(Igray);
[features, valid_points] = extractFeatures(Igray, points);
plot(valid_points.selectStrongest(100),'showOrientation',true);
title('SURF - points of interest');

%Find points of interest form truck.raw
input = 'truck.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
figure(4)
Igray = uint8(Igray);
imshow(I); hold on;
points = detectSURFFeatures(Igray);
[features, valid_points] = extractFeatures(Igray, points);
plot(valid_points.selectStrongest(100),'showOrientation',true);
title('SURF - points of interest');


%% Part b - Image Matching
% SIFT
%Convertibles
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
peak_threshold = 10; edge_threshold = 100;
[f1,d1] = vl_sift(Igray1,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

input = 'convertible_2.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
[f2,d2] = vl_sift(Igray2,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

figure(5)
imshow([I1,I2]);
length = size(I1,2) ; %length difference of the second concatenated image

%Find new matches
[matches, scores] = vl_ubcmatch(f1,f2) ;
f1 = f1(:,matches(1,:)); f2 = f2(:,matches(2,:));

% Show matches
line([f1(1,:);f2(1,:)+length],[f1(2,:);f2(2,:)],'Color','red') ;
title('SIFT Image Matching for convertible x.raw');

% Add colored numbers for displaying purposes
for i=1:size(f1,2)
    pos = sprintf('%d',i);
    text(f1(1,i),f1(2,i),pos, 'Color', 'g');
    text(f2(1,i)+length,f2(2,i),pos, 'Color', 'g');
end

NumberMatches_CNV_CNV =  size(matches,2) 

%Convertible_1 and SUV
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
peak_threshold = 10; edge_threshold = 100;
[f1,d1] = vl_sift(Igray1,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

input = 'suv.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
[f2,d2] = vl_sift(Igray2,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

figure(6)
imshow([I1,I2]);
length = size(I1,2) ; %length difference of the second concatenated image

%Find new matches
[matches, scores] = vl_ubcmatch(f1,f2) ;
f1 = f1(:,matches(1,:)); f2 = f2(:,matches(2,:));

% Show matches
line([f1(1,:);f2(1,:)+length],[f1(2,:);f2(2,:)],'Color','red') ;
title('SIFT Image Matching for convertible 1 and SUV');

% Add colored numbers for displaying purposes
for i=1:size(f1,2)
    pos = sprintf('%d',i);
    text(f1(1,i),f1(2,i),pos, 'Color', 'g');
    text(f2(1,i)+length,f2(2,i),pos, 'Color', 'g');
end

NumberMatches_CNV_SUV =  size(matches,2) 


%Convertible_1 and truck
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
peak_threshold = 10; edge_threshold = 100;
[f1,d1] = vl_sift(Igray1,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

input = 'truck.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
[f2,d2] = vl_sift(Igray2,'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);

figure(7)
imshow([I1,I2]);
length = size(I1,2) ; %length difference of the second concatenated image

%Find new matches
[matches, scores] = vl_ubcmatch(f1,f2) ;
f1 = f1(:,matches(1,:)); f2 = f2(:,matches(2,:));

% Show matches
line([f1(1,:);f2(1,:)+length],[f1(2,:);f2(2,:)],'Color','red') ;
title('SIFT Image Matching for convertible 1 and truck');

% Add colored numbers for displaying purposes
for i=1:size(f1,2)
    pos = sprintf('%d',i);
    text(f1(1,i),f1(2,i),pos, 'Color', 'g');
    text(f2(1,i)+length,f2(2,i),pos, 'Color', 'g');
end

NumberMatches_CNV_TRK =  size(matches,2) 
%%
% SURF
%Convertibles
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
input = 'convertible_2.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
Igray1 = uint8(Igray1);
Igray2 = uint8(Igray2);
points1 = detectSURFFeatures(Igray1,'MetricThreshold',10);
points2 = detectSURFFeatures(Igray2,'MetricThreshold',10);
points1 = points1.selectStrongest(50);
points2 = points2.selectStrongest(50);
[f1,v1]= extractFeatures(Igray1,points1);
[f2,v2]= extractFeatures(Igray2,points2);
pairs = matchFeatures(f1,f2,'MatchThreshold',20);
matchedP1 = v1(pairs(:,1));
matchedP2 = v2(pairs(:,2));
figure(8)
showMatchedFeatures(I1,I2,matchedP1,matchedP2,'montage');
legend('Matching Points conv_1','Matching Points conv_2');

%Convertible vs suv
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
input = 'suv.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
Igray1 = uint8(Igray1);
Igray2 = uint8(Igray2);
points1 = detectSURFFeatures(Igray1,'MetricThreshold',10);
points2 = detectSURFFeatures(Igray2,'MetricThreshold',10);
points1 = points1.selectStrongest(50);
points2 = points2.selectStrongest(50);
[f1,v1]= extractFeatures(Igray1,points1);
[f2,v2]= extractFeatures(Igray2,points2);
pairs = matchFeatures(f1,f2,'MatchThreshold',20);
matchedP1 = v1(pairs(:,1));
matchedP2 = v2(pairs(:,2));
figure(9)
showMatchedFeatures(I1,I2,matchedP1,matchedP2,'montage');
legend('Matching Points conv_1','Matching Points suv');

%Convertible vs truck
input = 'convertible_1.raw';
[I1,Igray1] = rawtoGrayscale(input,row,cols,bytes);
input = 'truck.raw';
[I2,Igray2] = rawtoGrayscale(input,row,cols,bytes);
Igray1 = uint8(Igray1);
Igray2 = uint8(Igray2);
points1 = detectSURFFeatures(Igray1,'MetricThreshold',10);
points2 = detectSURFFeatures(Igray2,'MetricThreshold',10);
points1 = points1.selectStrongest(50);
points2 = points2.selectStrongest(50);
[f1,v1]= extractFeatures(Igray1,points1);
[f2,v2]= extractFeatures(Igray2,points2);
pairs = matchFeatures(f1,f2,'MatchThreshold',20);
matchedP1 = v1(pairs(:,1));
matchedP2 = v2(pairs(:,2));
figure(10)
showMatchedFeatures(I1,I2,matchedP1,matchedP2,'montage');
legend('Matching Points conv_1','Matching Points truck');


%% Part c - Bag of Words
row = 500;
cols = 300;
bytes = 3;
k=8;

%Find cluster centers for suv.raw
input = 'suv.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
% Set parameters
peak_threshold = 8; edge_threshold = 100;
[f,descriptor1] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);
%clusters1 = yael_kmeans(single(descriptor1),k);
clusters1 = learnCodebook(descriptor1,k);
%Find the histogram - bag of words histogram
hist1 = computeBoV(clusters1,descriptor1,0);

%Find cluster centers for truck.raw
input = 'truck.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
% Set parameters 
peak_threshold = 10; edge_threshold = 100;
[f,descriptor2] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);
clusters2 = learnCodebook(descriptor2,k);
%Find the histogram - bag of words histogram
hist2 = computeBoV(clusters2,descriptor2,0);

%Find cluster centers for convertible_1.raw
input = 'convertible_1.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
% Set parameters 
peak_threshold = 10; edge_threshold = 100;
[f,descriptor3] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);
clusters3 = learnCodebook(descriptor3,k);
%Find the histogram - bag of words histogram
hist3 = computeBoV(clusters3,descriptor3,0);

%Find cluster centers for convertible_2.raw
input = 'convertible_2.raw';
[I,Igray] = rawtoGrayscale(input,row,cols,bytes);
% Set parameters 
peak_threshold = 10; edge_threshold = 100;
[f,descriptor4] = vl_sift(Igray, 'PeakThresh', peak_threshold, ...
'edgethresh', edge_threshold);
clusters4 = learnCodebook(descriptor4,k);
%Find the histogram - bag of words histogram
hist4 = computeBoV(clusters4,descriptor4,0);

%Combining all the histograms in one matrix
trainData = [hist1,hist2,hist3];
trainLabels = [1,2,3];
testData = [hist4];

finalLabel = SVM(trainLabels,trainData,testData)
%-> finalLabel = 3

%Visualize the codebook
%sift_descriptors = {descriptor1; descriptor2; ...
%    descriptor3; descriptor4};
%C = (clusters1+clusters2+clusters3+clusters4)/4;
%    A = DescriptorSoftCode(sift_descriptors,clusters4);
