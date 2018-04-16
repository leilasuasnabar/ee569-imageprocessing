% 569 Homework Assignment 3
% Date: March 25th,2017
% Name: Leila Suasnabar
% ID: 3109-9816-56
% email: lsuasnabar@usc.edu
%
% Problem 2b. Run in matlab. Structured Edge Detection
% See more details in the function description

%Same for all images
cols = 481;
row = 321;

hold all;
figure(1)
[edge,probMap] = SEDetection('Castle.raw', 'CastleSE_002.raw', 0.02,cols,row);
imshow(edge);
title('Castle with a threshold of 0.02');

figure(2)
im(1-probMap);
title('Probability Map for Castle.raw');

figure(3)
[edge,~] = SEDetection('Castle.raw', 'CastleSE_005.raw', 0.05,cols,row);
imshow(edge);
title('Castle with a threshold of 0.05');

figure(4)
[edge,~] = SEDetection('Castle.raw', 'CastleSE_010.raw', 0.10,cols,row);
imshow(edge);
title('Castle with a threshold of 0.10');

figure(5)
[edge,~] = SEDetection('Castle.raw', 'CastleSE_015.raw', 0.15,cols,row);
imshow(edge);
title('Castle with a threshold of 0.15');

figure(6)
[edge,~] = SEDetection('Castle.raw', 'CastleSE_020.raw', 0.20,cols,row);
imshow(edge);
title('Castle with a threshold of 0.20');

figure(7)
[edge,~] = SEDetection('Castle.raw', 'CastleSE_025.raw', 0.25,cols,row);
imshow(edge);
title('Castle with a threshold of 0.25');

%Repeat for Boat.raw
figure(8)
[edge,probMap] = SEDetection('Boat.raw', 'BoatSE_002.raw', 0.02,cols,row);
imshow(edge);
title('Boat with a threshold of 0.02');

figure(9)
im(1-probMap);
title('Probability Map for Boat.raw');

figure(10)
[edge,~] = SEDetection('Boat.raw', 'BoatSE_005.raw', 0.05,cols,row);
imshow(edge);
title('Boat with a threshold of 0.05');

figure(11)
[edge,~] = SEDetection('Boat.raw', 'BoatSE_010.raw', 0.10,cols,row);
imshow(edge);
title('Boat with a threshold of 0.10');

figure(12)
[edge,~] = SEDetection('Boat.raw', 'BoatSE_015.raw', 0.15,cols,row);
imshow(edge);
title('Boat with a threshold of 0.15');

figure(13)
[edge,~] = SEDetection('Boat.raw', 'BoatSE_020.raw', 0.20,cols,row);
imshow(edge);
title('Boat with a threshold of 0.20');

figure(14)
[edge,probMap] = SEDetection('Boat.raw', 'BoatSE_025.raw', 0.25,cols,row);
imshow(edge);
title('Boat with a threshold of 0.25');


