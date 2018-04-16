function [ testLabel ] = SVM(trainLabels,trainData,testData)
%SVM since the training data only comes from 3 images
%   the euclidean distances are computed and compared 
%   against the 1D vector testData to produce a scalar value 
%   for the label

[codewords,images] = size(trainData);
distances = zeros(images,1);

for i=1:images
    dist = 0;
    for j=1:codewords
        dist = dist + (testData(j)-trainData(j,i))^2;
    end
    dist = sqrt(dist);
    %Final euclidean distances
    distances(i) = dist;
end

distances
%Compute the label
min = 100000;
for i=1:images
    
    if distances(i)<min
        min = distances(i);
        testLabel = trainLabels(i);
    end
    
end

end

