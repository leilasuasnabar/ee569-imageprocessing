function [ data ] = rawtoData(input,row,cols)
%RAWTODATA takes a raw file and outputs its data - [hxw]
%   only for 8-bit raw files.

fid = fopen(input, 'r');
size = row*cols;
if (fid == -1)
    error('Image cannot be opened \n');
    pause
end

%Read image
temp = fread(fid,size,'uchar');
fclose(fid);
counter = 1;
temp = uint8(temp);
%data - [h x w] 
data = ones(row, cols);

%Passing to I
for i = 1:row
    for j = 1:cols
        data(i,j) = temp(counter,1);
        counter = counter + 1;
    end;
end;
data = uint8(data);

end

