function [ classifier ] = classify(samples,mean,classes,F)
%CLASSIFY takes as inputs the vector samples, a vector class label of the 
%samples, and the sample mean as a matrix (2 features only) and the
%number of classes
%
%   Classify returns a vector classifier containing the new class labels
%   and a vector error which stores in the ith row
%   the error rate for ith class
 
[sz,~] = size(samples); %sz contains the sample size
classifier = zeros(sz,1); %stores the new label class

for i = 1:sz
    dist1 = 0;
    dist2 = 0;
    dist3 = 0;
    dist4 = 0;
    %Classifying new data
    if classes == 4
        for j=1:F
            dist1 = (samples(i,j) - mean(1,j))^2 + dist1;
            dist2 = (samples(i,j) - mean(2,j))^2 + dist2;
            dist3 = (samples(i,j) - mean(3,j))^2 + dist3;
            dist4 = (samples(i,j) - mean(4,j))^2 + dist4;
        end
        dist1 = sqrt(dist1);
        dist2 = sqrt(dist2);
        dist3 = sqrt(dist3);
        dist4 = sqrt(dist4);

        %Calculating the new Class Label
        if  dist2 > dist1 && dist3 > dist1 && dist4 > dist1
            classifier(i) = 1;
        elseif dist1 > dist2 && dist3 > dist2 && dist4 > dist2
            classifier(i) = 2;
        elseif dist1 > dist3 && dist2 > dist3 && dist4 > dist3
            classifier(i) = 3;
        else
            classifier(i) = 4;
        end
 
    elseif classes == 3
        f1 = samples(i,1);
        f2 = samples(i,2);

        dist1 = sqrt((f1-mean(1,1))^2 +(f2-mean(1,2))^2);
        dist2 = sqrt((f1-mean(2,1))^2 +(f2-mean(2,2))^2);
        dist3 = sqrt((f1-mean(3,1))^2 +(f2-mean(3,2))^2);
        
        %Calculating the new Class Label
        if  dist1>dist2
            if dist2>dist3
                classifier(i) = 3;
            else
                classifier(i) = 2;
            end
        else
            if dist1>dist3
                classifier(i) = 3;
            else
                classifier(i) = 1;
            end
        end   
        
    end
    
end

end
