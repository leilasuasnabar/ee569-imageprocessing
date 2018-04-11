//-----------------------------
//  EE 569 Assignment 2
//  Date: 02/14/17
//  Name: Leila Suasnabar
//-----------------------------

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "myFunctions.h"
#include <cmath>

# define PI           3.14159265358979323846  /* pi */

using namespace std;

ImageInfo::ImageInfo(){
    BytesPerPixel = 0;
    ImageSizeCols = 0;
    ImageSizeRows = 0;
    ImageName = "";
}

ImageInfo::ImageInfo(int bytes, int sizeCols, int sizeRows, std::string name){
    BytesPerPixel = bytes;
    ImageSizeCols = sizeCols;
    ImageSizeRows = sizeRows;
    ImageName = name;
}

void readImage(ImageInfo image, unsigned char *imageData,std::string folder){
    //Retrieve information from image
    int bytes = image.BytesPerPixel;
    int cols = image.ImageSizeCols;
    int rows = image.ImageSizeRows;
    std::string name = folder + image.ImageName;
    
    // Define file pointer
    FILE *file;
    // Read image into image data matrix
    if (!(file= fopen(name.c_str(),"rb"))) {
        cout << "Cannot open file: " << name << endl;
        exit(1);
    }
    fread(imageData, sizeof(unsigned char), rows*cols*bytes, file);
    fclose(file);
    
}

void writeImage(ImageInfo image,unsigned char *imageData){
    //Retrieve information from image
    int bytes = image.BytesPerPixel;
    int cols = image.ImageSizeCols;
    int rows = image.ImageSizeRows;
    std::string name = image.ImageName;
    
    // Define file pointer
    FILE *file;
    
    // Write image data from image data matrix
    if (!(file=fopen(name.c_str(),"wb"))) {
        cout << "Cannot open file: " << name << endl;
        exit(1);
    }
    
    fwrite(imageData, sizeof(unsigned char), rows*cols*bytes, file);
    fclose(file);
}

void datatotext(float *input,std::string name, int scale){
    std::string output = OUT_FOLDER + name + ".txt";
    //To store file
    ofstream hist(output);
    if (hist.is_open())
    {
        for(int index = 0; index<=255; index++){
            hist << input[index]*scale << endl;
        }
        
    }
    else{
        cout << "Unable to open file: " << name << endl;
        exit(2);
    }
    hist.close();
    
}


// PROBLEM 1

void doAffineWarping(ImageInfo image){
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    std::string output;

    // Allocate image data array and read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],IN_FOLDER);
    
    // Output array
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    
    // Make everything black first
    for(int i=0; i<image.ImageSizeRows ;i++){
        for(int j =0; j<image.ImageSizeCols ;j++){
            for(int k=0; k<image.BytesPerPixel;k++){
                imageOut[i][j][k] = 0;
            }
        }
    }

    //Variables for new positions
    int u,v;
    
    //Perform warping
    for(int i=0; i<image.ImageSizeRows ;i++){
        for(int j =0; j<image.ImageSizeRows ;j++){
            for(int k=0; k<image.BytesPerPixel;k++){

                //Block 1
                if (i<image.ImageSizeRows/2 && j< image.ImageSizeCols/2 && j<i){
                    u = 0.502*i+124;
                    v = -0.498*i+j+124;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 2
                else if(i<image.ImageSizeRows/2 && j< image.ImageSizeCols/2 && j>=i){
                    u = i-0.498*j+124;
                    v = 0.502*j+124;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 3
                else if(i<image.ImageSizeRows/2 && j>= image.ImageSizeCols/2 && j<image.ImageSizeCols-i){
                    u = i+0.4960*j-123.5;
                    v = 0.5*j+124.5;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 4
                else if(i<image.ImageSizeRows/2 && j>= image.ImageSizeCols/2 && j>=image.ImageSizeCols-i){
                    u = 0.502*i+124;
                    v = 0.502*i+j-125;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 5
                else if (i>=image.ImageSizeRows/2 && j>= image.ImageSizeCols/2 && j>=i){
                    u = 0.5*i+124.5;
                    v = -0.5*i+j+124.5;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 6
                else if (i>=image.ImageSizeRows/2 && j>= image.ImageSizeCols/2 && j<i){
                    u = i-0.5*j+124.5;
                    v = 0.5*j+124.5;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 7
                else if (i>=image.ImageSizeRows/2 && j< image.ImageSizeCols/2 && j>=image.ImageSizeCols-i){
                    u = i+0.502*j-125;
                    v = 0.502*j+124;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
                
                //Block 8
                else if (i>=image.ImageSizeRows/2 && j< image.ImageSizeCols/2 && j<image.ImageSizeCols-i){
                    u = 0.5*i+124.5;
                    v = 0.496*i+j-123.5;
                    imageOut[u][v][k] = imageData[i][j][k];
                }
            }
        }
    }

    output = OUT_FOLDER + input + "affineWarped.raw";
    
    //Write image into a new raw file
    image.ImageName = output;
    writeImage(image,&imageOut[0][0][0]);
}

void doWarping(ImageInfo image){
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    std::string output;
    
    // Allocate image data array and read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],IN_FOLDER);
    
    // Output array
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    int wide=0,new_j;
    
    // Make everything black first
    for(int i=0; i<image.ImageSizeRows ;i++){
        for(int j =0; j<image.ImageSizeCols ;j++){
            for(int k=0; k<image.BytesPerPixel;k++){
                imageOut[i][j][k] = 0;
            }
        }
    }
    
    //Perform warping and add black background
    for(int i=0; i<image.ImageSizeRows ;i++){
        if(i<image.ImageSizeRows/2) wide++;
        else wide--;
            for(int k=0; k<image.BytesPerPixel;k++){
                for(int m=0;m<2*wide;m++){
                    new_j = (m+1)*image.ImageSizeCols/(2*wide+1);
                    imageOut[i][250-wide+m][k] = imageData[i][new_j][k];
                }
            }
    }

    output = OUT_FOLDER + input + "Warped.raw";
    
    //Write image into a new raw file
    image.ImageName = output;
    writeImage(image,&imageOut[0][0][0]);
}

void solvePuzzle(ImageInfo pieces, ImageInfo image1, ImageInfo image2){
    std::string output;
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageData[pieces.ImageSizeRows][pieces.ImageSizeCols][pieces.BytesPerPixel];
    readImage(pieces,&imageData[0][0][0],IN_FOLDER);
    
    // Store data from first image
    unsigned char imageOne[image1.ImageSizeRows][image1.ImageSizeCols][image1.BytesPerPixel];
    readImage(image1, &imageOne[0][0][0],IN_FOLDER);
    
    // Store data from second image
    unsigned char imageTwo[image2.ImageSizeRows][image2.ImageSizeCols][image2.BytesPerPixel];
    readImage(image2, &imageTwo[0][0][0],IN_FOLDER);

    //Output corner positions on a file
    ofstream corners(OUT_FOLDER+"corners.txt");
    corners.is_open();
    corners << "\nPUZZLE MATCHING LOG\n";
    corners << "\nFirst image: " << image1.ImageName;
    corners << "\nSecond image: " << image2.ImageName << endl;
    
    
    //Find hole corner points, each hole is of size 100x100
    int i_hole[2];
    int j_hole[2];
    int index,counter=0;

    for(int i=1; i<image1.ImageSizeRows ;i++){
        for(int j=1; j<image1.ImageSizeCols ;j++){
            
            if(imageOne[i-1][j-1][0]!=255 && imageOne[i-1][j][0]!=255 && imageOne[i][j-1][0]!=255
                && imageOne[i][j][0]==255){
                i_hole[0] = i;
                j_hole[0] = j;
            }
            if(imageTwo[i-1][j-1][0]!=255 && imageTwo[i-1][j][0]!=255 && imageTwo[i][j-1][0]!=255
               && imageTwo[i][j][0]==255){
                i_hole[1] = i;
                j_hole[1] = j;
            }
        }
    }
    
    //Output corners of the holes
    string pix1[4]= {"Top left: ", "Top right: ", "Bottom left: ", "Bottom right: "};
    string position[2] = {"first","second"};
    for(int i=0;i<2;i++){
    corners << "\nCorner pixels of "<< position[i] <<" hole:\n";
    corners << pix1[0] << i_hole[i] << ", " << j_hole[i] << endl;
    corners << pix1[1] << i_hole[i] << ", " << j_hole[i] +99 << endl;
    corners << pix1[2] << i_hole[i] +99<< ", " << j_hole[i] << endl;
    corners << pix1[3] << i_hole[i] +99<< ", " << j_hole[i] +99<< endl;
    }
    
    //Find control points
    int box[9];
    int i_pos[8];
    int j_pos[8];
    
    for(int i=0; i<pieces.ImageSizeRows ;i++){
        for(int j=0; j<pieces.ImageSizeCols ;j++){
        
            //Check for nonbackground pixels
            if (imageData[i][j][0] != 255){
                index = 0;
                
                for(int m=-1; m<=1; m++){
                    for(int n=-1; n<=1; n++){
                        box[index] = imageData[i+m][j+n][0];
                        index ++;
                    }
                }
                
                //Find top left corner pixels
                if(box[0]>250 && box[1]>250 && box[2]>250 && box[3]>250 && box[4]!=255
                   && box[5]!=255 && box[6]>250 && box[7]!=255 && box[8]!=255){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find top right corner pixels
                if(box[0]>250 && box[1]>250 && box[2]>250 && box[3]!=250 && box[4]!=255
                   && box[5]>250 && box[6]!=255 && box[7]!=255 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find bottom left corner pixels
                if(box[0]>250 && box[1]!=255 && box[2]!=255 && box[3]>250 && box[4]!=255
                   && box[5]!=255 && box[6]>250 && box[7]>250 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find bottom right corner pixels
                if(box[0]!=255 && box[1]!=255 && box[2]>250 && box[3]!=250 && box[4]!=255
                   && box[5]>250 && box[6]>250 && box[7]>250 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
            }
        }
    }
    
    //Organize corner pixels orders as top left, top right, bottom left, bottom right
    string pix2[4]= {"Top right: ", "Top left: ", "Bottom right: ", "Bottom left: "};
    corners << "\nCorner pixels of first piece:\n";
    for (int i=0; i < 4; i++){
        corners << pix1[i] << i_pos[i] << ", " << j_pos[i] <<endl;
    }
    
    corners << "\nCorner pixels of second piece: \n";
    for (int i=4; i < 8; i++){
        corners << pix2[i-4] << j_pos[i] << ", " << i_pos[i] <<endl;
    }
    
    //Fillin holes
    int u,v;

    //Fill hole of the first image
    for(int i=0; i<pieces.ImageSizeRows/2 ;i++){
        for(int j =0; j<pieces.ImageSizeCols ;j++){
            for(int k=0; k<pieces.BytesPerPixel;k++){
                
                if(imageData[i][j][0]<250){
                
                    //Block 1
                    if (i<-0.5847*j+235.328){
                        //original+ extra after
                        u = 0.6439*i-0.1699*j+114.6083;
                        v = 0.1744*i+0.6484*j+100.8106;

                        if(u>=i_hole[0] && u<i_hole[0]+100 && v>=j_hole[0] && v< j_hole[0]+100)
                            imageOne[u][v][k] = imageData[i][j][k];
                    }
                    
                    //Block 2
                    else if(i>=-0.5847*j+235.328){
                        //original+ extra after
                        u = 0.6453*i-0.1691*j+114.2826;
                        v = 0.1756*i+0.6436*j+100.8462;

                        if(u>=i_hole[0] && u<i_hole[0]+100 && v>=j_hole[0] && v< j_hole[0]+100)
                            imageOne[u][v][k] = imageData[i][j][k];
                    }
                
                }
            }
        }
    }
    //Temporary variable for the sum of pixels
    int sum1,sum2;
    //Fix edges
    for(int k=0; k<image1.BytesPerPixel; k++){
        //Fix top and bottom
        for (int j=j_hole[0]; j<j_hole[0]+100; j++){
            sum1 = 0;
            sum2 = 0;
            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    if (n!=0){
                        sum1 += imageOne[i_hole[0]+100-1+n][j+m][k];
                        sum2 += imageOne[i_hole[0]+n][j+m][k];
                    }
                }
            }
            sum1 /= 6; //find average of neighbor pixels
            sum2 /= 6;
            
            imageOne[i_hole[0]+100-1][j][k] = sum1;
            imageOne[i_hole[0]][j][k] = sum2;
        }
    
        
        //Fix sides
        for (int i=i_hole[0]; i<i_hole[0]+100; i++){
            sum1 = 0;
            sum2 = 0;
            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    if (m!=0){
                        sum1 += imageOne[i+n][j_hole[0]+100-1+m][k];
                    }
                }
            }
            sum1 /= 6; //find average of neighbor pixels
            
            imageOne[i][j_hole[0]+100-1][k] = sum1;
        }
    }
    output = OUT_FOLDER + "solvedpuzzleHillary.raw";
    
    //Write image into a new raw file
    image1.ImageName = output;
    writeImage(image1,&imageOne[0][0][0]);

    

    //Fill hole of the first image
    //Perform bilinear interpolation to the small image
    int i_start = min(min(min(i_pos[4],i_pos[5]),i_pos[6]),i_pos[7])-2; //adding space for white lines
    int j_start = min(min(min(j_pos[4],j_pos[5]),j_pos[6]),j_pos[7])-2;
    int i_end = max(max(max(i_pos[4],i_pos[5]),i_pos[6]),i_pos[7])+2;
    int j_end = max(max(max(j_pos[4],j_pos[5]),j_pos[6]),j_pos[7])+2;
    
    // Store output
    int new_size = min(i_end-i_start,j_end-j_start);

    corners << "\nSize of isolated second piece: " << new_size << endl;

    unsigned char imageTemp[new_size][new_size][image2.BytesPerPixel];
    
    for(int i=0; i<new_size ;i++){
        for(int j =0; j<new_size ;j++){
            for(int k=0; k<pieces.BytesPerPixel;k++){
                imageTemp[i][j][k] = imageData[i+i_start][j+j_start][k];
            }
        }
    }
    output = IN_FOLDER + "temp.raw";
    
    //Write image into a new raw file
    ImageInfo temp(image2.BytesPerPixel,new_size,new_size,output);
    writeImage(temp,&imageTemp[0][0][0]);
    
    int new_resized = 120;
    bilinear(temp,new_resized,new_resized,"temp.raw");
    corners << "New resized image size: " << new_resized << endl;
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageResized[new_resized][new_resized][temp.BytesPerPixel];
    temp.ImageName = "temp.raw";
    temp.ImageSizeCols = new_resized;
    temp.ImageSizeRows = new_resized;
    readImage(temp,&imageResized[0][0][0],IN_FOLDER);

    //Find the corners of the resized image
    counter = 0;
    for(int i=0; i<new_size ;i++){
        for(int j=0; j<new_size ;j++){
            
            //Check for nonbackground pixels
            if (imageTemp[i][j][0] != 255){
                index = 0;
                
                for(int m=-1; m<=1; m++){
                    for(int n=-1; n<=1; n++){
                        box[index] = imageTemp[i+m][j+n][0];
                        index ++;
                    }
                }
                
                //Find top left corner pixels
                if(box[0]>250 && box[1]>250 && box[2]>250 && box[3]>250 && box[4]!=255
                   && box[5]!=255 && box[6]>250 && box[7]!=255 && box[8]!=255){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find top right corner pixels
                if(box[0]>250 && box[1]>250 && box[2]>250 && box[3]!=250 && box[4]!=255
                   && box[5]>250 && box[6]!=255 && box[7]!=255 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find bottom left corner pixels
                if(box[0]>250 && box[1]!=255 && box[2]!=255 && box[3]>250 && box[4]!=255
                   && box[5]!=255 && box[6]>250 && box[7]>250 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
                
                //Find bottom right corner pixels
                if(box[0]!=255 && box[1]!=255 && box[2]>250 && box[3]!=250 && box[4]!=255
                   && box[5]>250 && box[6]>250 && box[7]>250 && box[8]>250){
                    i_pos[counter] = i;
                    j_pos[counter] = j;
                    counter++;
                }
            }
        }
    }

    
    string pix3[4]= {"Top right: ", "Top left: ", "Bottom right: ", "Bottom left: "};
    corners << "\nCorner pixels of second piece after being resized:\n";
    for(int i=0; i < 4; i++){
        corners << pix3[i] << int(i_pos[i]*double(new_resized)/double(new_size)) << ", "
                << int(j_pos[i]*double(new_resized)/double(new_size)) <<endl;
    }
    
    //Fill hole in the second image
    for(int i=0; i<temp.ImageSizeRows ;i++){
        for(int j =0; j<temp.ImageSizeCols ;j++){
            for(int k=0; k<pieces.BytesPerPixel;k++){
                
                if(imageResized[i][j][0]!=255){
                    
                    //Block 1
                    if (j<-0.8621*i+111.72){
                        u = -0.0709*i+0.9577*j+232.7940;
                        v = -0.9570*i-0.0802*j+274.7306;
                        
                        if(u>=i_hole[1] && u<i_hole[1]+100 && v>=j_hole[1] && v< j_hole[1]+100)
                            imageTwo[u][v][k] = imageResized[i][j][k];
                    }
                    
                    //Block 2
                    else if(j>=-0.8621*i+111.72){
                        u = -0.0722*i+0.9563*j+232.9535;
                        v = -0.9650*i-0.0893*j+275.7582;
                        
                        if(u>=i_hole[1] && u<i_hole[1]+100 && v>=j_hole[1] && v< j_hole[1]+100)
                            imageTwo[u][v][k] = imageResized[i][j][k];
                    }
                }
            }
        }
    }

    //Fix edges
    for(int k=0; k<image2.BytesPerPixel; k++){
        //Fix top and bottom
        for (int j=j_hole[1]; j<j_hole[1]+100; j++){
            sum1 = 0;
            sum2 = 0;
            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    if (n!=0){
                        sum1 += imageTwo[i_hole[1]+n][j+m][k];
                        sum2 += imageTwo[i_hole[1]+100-1+n][j+m][k];
                    }
                }
            }
            sum1 /= 6; //find average of neighbor pixels
            sum2 /= 6;
            
            imageTwo[i_hole[1]][j][k] = sum1;
            imageTwo[i_hole[1]+100-1][j][k] = sum2;
        }
        
        //Fix sides
        for (int i=i_hole[1]; i<i_hole[1]+100; i++){
            sum1 = 0;
            sum2 = 0;
            for(int m=-1;m<=1;m++){
                for(int n=-1;n<=1;n++){
                    if (m!=0){
                        sum1 += imageTwo[i+n][j_hole[1]+m][k];
                        sum2 += imageTwo[i+n][j_hole[1]+100-1+m][k];
                    }
                }
            }
            sum1 /= 6; //find average of neighbor pixels
            sum2 /= 6;
            
            imageTwo[i][j_hole[1]][k] = sum1;
            imageTwo[i][j_hole[1]+100-1][k] = sum2;
        }
    }
    
    //Fix small white holes
    for (int j=j_hole[1]; j<j_hole[1]+100; j++){
        for (int i=i_hole[1]; i<i_hole[1]+100; i++){
            for(int k=0; k<image2.BytesPerPixel; k++){
                sum1 = 0;
                if (imageTwo[i][j][k]==255){
                    for(int m=-1; m<=1; m++){
                        for(int n=-1; n<=1; n++){
                            sum1+=imageTwo[i+m][j+n][k];
                        }
                    }
                    
                    sum1 -= imageTwo[i][j][k];
                    sum1 /= 8; //average surrounding pixels
                    
                    imageTwo[i][j][k] = sum1;
                }
                
            }
        }
    }
    
    /*
    //Smooth the area
    //Fix small white holes
     for (int j=j_hole[1]; j<j_hole[1]+100; j++){
        for (int i=i_hole[1]; i<i_hole[1]+100; i++){
            for(int k=0; k<image2.BytesPerPixel; k++){
                sum1 = 0;
                for(int m=-1; m<=1; m++){
                    for(int n=-1; n<=1; n++){
                        sum1+=imageTwo[i+m][j+n][k];
                    }
                }
                sum1 -= imageTwo[i][j][k];
                sum1 *= (0.05/8);
 
                imageTwo[i][j][k] = sum1 + imageTwo[i][j][k]*0.95;
                
            }
        }
    }*/

    corners.close();
    
    output = OUT_FOLDER + "solvedpuzzleTrump.raw";
    
    //Write image into a new raw file
    image2.ImageName = output;
    writeImage(image2,&imageTwo[0][0][0]);

}


void bilinear(ImageInfo image, double resize_rows, double resize_cols,string name){
    double point_x,point_y,a,b,residue;
    int ref_i, ref_j;
    
    //Allocating memory for new resized data
    unsigned char resized[int(resize_rows)][int(resize_cols)][image.BytesPerPixel];
    
    // Image data
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    image.ImageName = name;
    readImage(image,&imageData[0][0][0],IN_FOLDER);
    
    //resize_size array contain x desired pixel length in position 0
    //and y desired pixel length in position 1
    double scale_x = image.ImageSizeRows/resize_rows; //scaling factors
    double scale_y = image.ImageSizeCols/resize_cols;
    
    //Resizing through bilinear interpolation
    for(int i=0; i<resize_rows ;i++){
        for(int j =0; j<resize_cols ;j++){
            //new ratio from original pixel to resized pixel
            point_x = i*scale_x;
            point_y = j*scale_y;
            //position of new pixel with respect to the reference pixel from the original image
            //modf returns the decimal part of input
            a = modf(point_y,&residue);
            b = modf(point_x,&residue);
            
            //reference pixel position
            ref_i = point_x-b;
            ref_j = point_y-a;
            
            for(int k=0; k<image.BytesPerPixel ;k++){
                resized[i][j][k] = int((1-b)*((1-a)*imageData[ref_i][ref_j][k] +
                                              a*imageData[ref_i+1][ref_j][k]) + b*((1-a)*imageData[ref_i][ref_j+1][k] + a*imageData[ref_i+1][ref_j+1][k]));
            }
        }
    }
    string output = IN_FOLDER + "temp.raw";
    //Write image into a new raw file
    ImageInfo temp(image.BytesPerPixel,resize_cols,resize_rows,output);
    writeImage(temp,&resized[0][0][0]);
    
}


void homographicTran(ImageInfo image1, ImageInfo image2){
    std::string output;
    std::string location = image1.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    unsigned char imageOut[image1.ImageSizeRows][image1.ImageSizeCols][image1.BytesPerPixel];
    readImage(image1,&imageOut[0][0][0],IN_FOLDER);

    int u=0,v=0;
    float w,x,y,a,b;
    
    //Resize image
    int resize_rows = 1.5*image2.ImageSizeRows;
    int resize_cols = 1.5*image2.ImageSizeCols;
    bilinear(image2,resize_rows,resize_cols,image2.ImageName);
    
    image2.ImageName = "temp.raw";
    unsigned char imageData[resize_rows][resize_cols][image2.BytesPerPixel];
    image2.ImageSizeCols = resize_cols;
    image2.ImageSizeRows = resize_rows;
    readImage(image2,&imageData[0][0][0],IN_FOLDER);
    
    //Find H transformation matrix
    //Perform warping
    for(int i=0; i<resize_rows ;i++){
        for(int j =0; j<resize_cols;j++){
            for(int k=0; k<image2.BytesPerPixel;k++){
                
                if(imageData[i][j][0]<245){
                    x = -0.05602854638788*i+0.434016451022738*j+595;
                    y = 0.598343893526434*i+1.369389489556119*j+322;
                    w = -0.000175490089428*i +0.001758688647428*j+ 1;
                    
                    //Setting up from homogenous to cartesian coordinates
                    u = x/w;
                    v = y/w;
                    

                }
                //Overlay
                b = imageData[i][j][k]/255.0;
                a = imageOut[u][v][k]/255.0;
                //b *= 0.95;
 
                if(a<0.5) imageOut[u][v][k] = 2*a*b*255;
                else    imageOut[u][v][k] = (1-2*(1-a)*(1-b))*255;
            }
        }
    }
    
    output = OUT_FOLDER + input + "Transformed.raw";
    //Write image into a new raw file
    image1.ImageName = output;
    writeImage(image1,&imageOut[0][0][0]);
    remove("Inputs/temp.raw");
    
}

void dithering(ImageInfo image, int n){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    n /= 2;
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],IN_FOLDER);
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    
    // matrix A
    double A[4][4] = {14,10,11,15,9,3,0,4,8,2,1,5,13,7,6,12};
    double T;
    double I2[2*n][2*n];
    if (n!=0){ // Check if we're using an A dithering matrix
        double I[2][2] = {0,2,3,1};
        int counter = 1;
        int n_temp = 2;
        while(counter<2*n){
            //Creating the 2*n dithering matrix
            for (int i=0; i<n_temp/2; i++){
                for(int j=0; j<n_temp/2; j++){
                    I2[i][j] = 4*I[i][j];
                }
                for(int j=n_temp/2; j<n_temp; j++){
                    I2[i][j] = 4*I[i][j-n_temp/2] + 2;
                }
            }
            
            for (int i=n_temp/2; i<n_temp; i++){
                for(int j=0; j<n_temp/2; j++){
                    I2[i][j] = 4*I[i-n_temp/2][j] + 3;
                }
                for(int j=n_temp/2; j<n_temp; j++){
                    I2[i][j] = 4*I[i-n_temp/2][j-n_temp/2] + 1;
                }
            }
            n_temp *= 2;
            counter *=  2;
        }
        
        int N = 2*n;
        for (int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                
                //Find the threshold value
                T = 255.0*(I2[i%N][j%N]+0.5)/double(N*N);
                
                if (imageData[i][j]>T){
                    imageOut[i][j] = 255;
                }
                else
                    imageOut[i][j] = 0;
                
            }
        }
        
        output = OUT_FOLDER + input + "_dithered" + to_string(2*n) +".raw";
        //Write image into a new raw file
        image.ImageName = output;
        writeImage(image,&imageOut[0][0]);
        
        if(n==2){
            output = IN_FOLDER + input + "_dithered" + to_string(2*n) +".raw";
            //Write image into a new raw file
            image.ImageName = output;
            writeImage(image,&imageOut[0][0]);
        }
        
    }

    else{
        int N = 2*2;
        for (int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                
                //Find the threshold value
                T = 255.0*(A[i%N][j%N]+0.5)/double(N*N);
                
                if (imageData[i][j]>T){
                    imageOut[i][j] = 255;
                }
                else
                    imageOut[i][j] = 0;
                
            }
        }
        
        output = OUT_FOLDER + input + "_ditheredA.raw";
        //Write image into a new raw file
        image.ImageName = output;
        writeImage(image,&imageOut[0][0]);
        
        output = IN_FOLDER + input + "_ditheredA.raw";
        //Write image into a new raw file
        image.ImageName = output;
        writeImage(image,&imageOut[0][0]);
        
    }

}

void dithering4(ImageInfo image, int n){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    n /= 2;
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],IN_FOLDER);
    
    // Allocate image data array and read image that has the pieces
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    
    // matrix A
    double A[4][4] = {14,10,11,15,9,3,0,4,8,2,1,5,13,7,6,12};
    double T;
    double I2[2*n][2*n];
    if (n!=0){ // Check if we're using an A dithering matrix
        double I[2][2] = {0,2,3,1};
        int counter = 1;
        int n_temp = 2;
        while(counter<2*n){
            //Creating the 2*n dithering matrix
            for (int i=0; i<n_temp/2; i++){
                for(int j=0; j<n_temp/2; j++){
                    I2[i][j] = 4*I[i][j];
                }
                for(int j=n_temp/2; j<n_temp; j++){
                    I2[i][j] = 4*I[i][j-n_temp/2] + 2;
                }
            }
            
            for (int i=n_temp/2; i<n_temp; i++){
                for(int j=0; j<n_temp/2; j++){
                    I2[i][j] = 4*I[i-n_temp/2][j] + 3;
                }
                for(int j=n_temp/2; j<n_temp; j++){
                    I2[i][j] = 4*I[i-n_temp/2][j-n_temp/2] + 1;
                }
            }
            n_temp *= 2;
            counter *=  2;
        }
        
        int N = 2*n;
        for (int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                
                //Find the threshold value
                T = 255.0*(I2[i%N][j%N]+0.5)/double(N*N);
                
                if (imageData[i][j]>5*T/3)
                    imageOut[i][j] = 255;
                
                else if(imageData[i][j]>4*T/3 && imageData[i][j]<=5*T/3)
                    imageOut[i][j] = 170;
                
                else if(imageData[i][j] > T && imageData[i][j] <= 4*T/3)
                    imageOut[i][j] = 85;
                else
                    imageOut[i][j] = 0;
            }
        }
        
        output = OUT_FOLDER + input + "_ditheredFOUR" + to_string(2*n) +".raw";
        //Write image into a new raw file
        image.ImageName = output;
        writeImage(image,&imageOut[0][0]);

    }
    
    else{
        int N = 2*2;
        for (int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                
                //Find the threshold value
                T = 255.0*(A[i%N][j%N]+0.5)/double(N*N);
                
                if (imageData[i][j]>5*T/3)
                    imageOut[i][j] = 255;
                
                else if(imageData[i][j]>4*T/3 && imageData[i][j]<=5*T/3)
                    imageOut[i][j] = 170;
                
                else if(imageData[i][j] > T && imageData[i][j] <= 4*T/3)
                    imageOut[i][j] = 85;
                else
                    imageOut[i][j] = 0;
            }
        }
        
        output = OUT_FOLDER + input + "_ditheredFOURA.raw";
        //Write image into a new raw file
        image.ImageName = output;
        writeImage(image,&imageOut[0][0]);
        
    }
}

void expandImage(ImageInfo image, int window){
    
    std::string location = image.ImageName;
    std::string output;
    
    window = (window-1)/2; //extra rows/cols needed
    
    // Allocate image data array and read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],IN_FOLDER);
    
    // Allocate image data array for extended image
    unsigned char imageExt[image.ImageSizeRows+2*window]
    [image.ImageSizeCols+2*window][image.BytesPerPixel];
    
    for(int k=0; k<image.BytesPerPixel; k++){
        
        for(int j=0; j<image.ImageSizeRows+2*window ;j++){
            for(int i=0; i<image.ImageSizeCols+2*window;i++){
                imageExt[i][j][k] = 0;
            }
        }
        
        //Add image to the center
        for(int j=0; j<image.ImageSizeRows ;j++){
            for(int i=0; i<image.ImageSizeCols ;i++){
                imageExt[i+window][j+window][k] = imageData[i][j][k];
            }
        }
        
        
        //Add extra pixels on the top and bottom
        for(int j=0; j<image.ImageSizeCols ;j++){
            for(int i=0; i<window ;i++){
                imageExt[i][j+window][k] = imageData[i][j][k];
            }
            for(int i=image.ImageSizeRows+window; i<image.ImageSizeRows+2*window; i++){
                imageExt[i][j+window][k] = imageData[i-2*window][j][k];
            }
        }
        
        //Add extra pixels on the sides
        for(int i=0; i<image.ImageSizeRows + 2*window ;i++){
            for(int j=0; j<window ;j++){
                imageExt[i][j][k] = imageExt[i][j+window][k];
            }
            for(int j=image.ImageSizeCols; j<image.ImageSizeCols+window; j++){
                imageExt[i][j+window][k] = imageExt[i][j][k];
            }
        }
    }
    
    //Writes files in the inputs folder
    output = IN_FOLDER + "imageExpanded.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows+2*window,image.ImageSizeCols+2*window,output);
    writeImage(result,&imageExt[0][0][0]);
    
}


void errorDifussion(ImageInfo image,std::string type){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    int window;
    int extra,counter;
    double sum;
    //Checking the error diffusion type
    if (type == "Floyd-Steinberg"){
        window = 3;
        extra =(window-1)/2; //extra rows/cols on a side of the image
        expandImage(image,window);
        float box1[9] = {0.0,0.0,0.0,0.0,0.0,7.0/16,3.0/16,5.0/16,1.0/16};
        float box2[9] = {0.0,0.0,0.0,7.0/16,0.0,0.0,1.0/16,5.0/16,3.0/16};
        
        // Output image data
        unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
        // Allocate image data array and read image
        image.ImageSizeCols += 2*extra;
        image.ImageSizeRows += 2*extra;
        image.ImageName = "imageExpanded.raw";
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);

        
        for(int i= extra; i<image.ImageSizeRows-extra; i++){
            if(i%2!=0){//Move from left to right
                for(int j=extra; j<image.ImageSizeCols-extra; j++){

                    counter = 0;
                    sum = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            sum += imageData[i+n][j+m]*box1[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
            
            else{ //Move from right to left
                for(int j=image.ImageSizeCols-extra-1; j>extra-1; j--){
                    
                    counter = 0;
                    sum = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            sum += imageData[i+n][j+m]*box2[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
        }
        
        //Fix to correct size
        for(int j=extra; j<image.ImageSizeRows-extra; j++){
            for(int i=extra; i<image.ImageSizeCols-extra; i++){
                imageOut[i-extra][j-extra] = imageData[i][j];
            }
        }
        
        //Writes files in the inputs folder
        output = OUT_FOLDER + input+ "_Floyd-Steinberg.raw";
        
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows-2*extra,image.ImageSizeCols-2*extra,output);
        writeImage(result,&imageOut[0][0]);
        
        
    }

    
    else if (type == "JJN"){
        window = 5;
        extra =(window-1)/2; //extra rows/cols on a side of the image
        expandImage(image,window);
        float box1[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,7.0/48,5.0/48,3.0/48,5.0/48,7.0/48,5.0/48,3.0/48,
            1.0/48,3.0/48,5.0/48,3.0/48,1.0/48};
        float box2[25] = {0,0,0,0,0,0,0,0,0,0,5.0/48,7.0/48,0,0,0,3.0/48,5.0/48,7.0/48,5.0/48,3.0/48,
            1.0/48,3.0/48,5.0/48,3.0/48,1.0/48};
        
        // Output image data
        unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
        // Allocate image data array and read image
        image.ImageSizeCols += 2*extra;
        image.ImageSizeRows += 2*extra;
        image.ImageName = "imageExpanded.raw";
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);
        
        
        for(int i= extra; i<image.ImageSizeRows-extra; i++){
            if(i%2==0){//Move from left to right
                for(int j=extra; j<image.ImageSizeCols-extra; j++){
                    counter = 0;
                    sum = 0;
                    for(int n=-2;n<=2;n++){
                        for(int m=-2;m<=2;m++){
                            sum += imageData[i+n][j+m]*box1[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
            
            else{ //Move from right to left
                for(int j=image.ImageSizeCols-extra-1; j>extra-1; j--){
                    
                    counter = 0;
                    sum = 0;
                    for(int n=-2;n<=2;n++){
                        for(int m=-2;m<=2;m++){
                            sum += imageData[i+n][j+m]*box2[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
        }
        
        //Fix to correct size
        for(int j=extra; j<image.ImageSizeRows-extra; j++){
            for(int i=extra; i<image.ImageSizeCols-extra; i++){
                imageOut[i-extra][j-extra] = imageData[i][j];
            }
        }
        
        //Writes files in the inputs folder
        output = OUT_FOLDER + input+ "_JJN.raw";
        
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows-2*extra,image.ImageSizeCols-2*extra,output);
        writeImage(result,&imageOut[0][0]);
    }


    else if (type == "Stucki"){
        window = 5;
        extra =(window-1)/2; //extra rows/cols on a side of the image
        expandImage(image,window);
        float box1[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,8.0/42,4.0/42,2.0/42,4.0/42,8.0/42,4.0/42,2.0/42,
            1.0/42,2.0/42,4.0/42,2.0/42,1.0/42};
        float box2[25] = {0,0,0,0,0,0,0,0,0,0,4.0/42,8.0/42,0,0,0,2.0/42,4.0/42,8.0/42,4.0/42,2.0/42,
            1.0/42,2.0/42,4.0/42,2.0/42,1.0/42};
        
        // Output image data
        unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
        // Allocate image data array and read image
        image.ImageSizeCols += 2*extra;
        image.ImageSizeRows += 2*extra;
        image.ImageName = "imageExpanded.raw";
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);
        
        
        for(int i= extra; i<image.ImageSizeRows-extra; i++){
            if(i%2==0){//Move from left to right
                for(int j=extra; j<image.ImageSizeCols-extra; j++){
                    counter = 0;
                    sum = 0;
                    for(int n=-2;n<=2;n++){
                        for(int m=-2;m<=2;m++){
                            sum += imageData[i+n][j+m]*box1[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
            
            else{ //Move from right to left
                for(int j=image.ImageSizeCols-extra-1; j>extra-1; j--){
                    
                    counter = 0;
                    sum = 0;
                    for(int n=-2;n<=2;n++){
                        for(int m=-2;m<=2;m++){
                            sum += imageData[i+n][j+m]*box2[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
        }
        
        //Fix to correct size
        for(int j=extra; j<image.ImageSizeRows-extra; j++){
            for(int i=extra; i<image.ImageSizeCols-extra; i++){
                imageOut[i-extra][j-extra] = imageData[i][j];
            }
        }
        
        //Writes files in the inputs folder
        output = OUT_FOLDER + input+ "_Stucki.raw";
        
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows-2*extra,image.ImageSizeCols-2*extra,output);
        writeImage(result,&imageOut[0][0]);
    }
    
    
    //Trying new method
    else{
        window = 3;
        extra =(window-1)/2; //extra rows/cols on a side of the image
        expandImage(image,window);
        float box1[9] = {0.0,0.0,0.0,0.0,0.0,1.0/16,3.0/16,5.0/16,7.0/16};
        float box2[9] = {0.0,0.0,0.0,1.0/16,0.0,0.0,7.0/16,5.0/16,3.0/16};
        
        
        // Output image data
        unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
        // Allocate image data array and read image
        image.ImageSizeCols += 2*extra;
        image.ImageSizeRows += 2*extra;
        image.ImageName = "imageExpanded.raw";
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);
        
        
        for(int i= extra; i<image.ImageSizeRows-extra; i++){
            if(i%2!=0){//Move from left to right
                for(int j=extra; j<image.ImageSizeCols-extra; j++){
                    
                    counter = 0;
                    sum = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            sum += imageData[i+n][j+m]*box1[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
            
            else{ //Move from right to left
                for(int j=image.ImageSizeCols-extra-1; j>extra-1; j--){
                    
                    counter = 0;
                    sum = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            sum += imageData[i+n][j+m]*box2[counter];
                            counter++;
                        }
                    }
                    imageData[i][j] = sum;
                }
            }
        }
        
        //Fix to correct size
        for(int j=extra; j<image.ImageSizeRows-extra; j++){
            for(int i=extra; i<image.ImageSizeCols-extra; i++){
                imageOut[i-extra][j-extra] = imageData[i][j];
            }
        }
        
        //Writes files in the inputs folder
        output = OUT_FOLDER + input+ "_NewMethod.raw";
        
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows-2*extra,image.ImageSizeCols-2*extra,output);
        writeImage(result,&imageOut[0][0]);
        
    }
}


int checkMarkPattern(int *stack,std::string type,std::string method){

    int condPattern[66][9] =   {0,0,1,0,1,0,0,0,0,  1,0,0,0,1,0,0,0,0,  0,0,0,0,1,0,1,0,0,  0,0,0,0,1,0,0,0,1, //S1
                                0,0,0,0,1,1,0,0,0,  0,1,0,0,1,0,0,0,0,  0,0,0,1,1,0,0,0,0,  0,0,0,0,1,0,0,1,0, //S2
                                0,0,1,0,1,1,0,0,0,  0,1,1,0,1,0,0,0,0,  1,1,0,0,1,0,0,0,0,  1,0,0,1,1,0,0,0,0, //S3
                                0,0,0,1,1,0,1,0,0,  0,0,0,0,1,0,1,1,0,  0,0,0,0,1,0,0,1,1,  0,0,0,0,1,1,0,0,1,
                                1,1,0,0,1,1,0,0,0,  0,1,0,0,1,1,0,0,1,  0,1,1,1,1,0,0,0,0,  0,0,1,0,1,1,0,1,0, //ST5
                                0,1,1,0,1,1,0,0,0,  1,1,0,1,1,0,0,0,0,  0,0,0,1,1,0,1,1,0,  0,0,0,0,1,1,0,1,1,
                                1,1,0,0,1,1,0,0,1,  0,1,1,1,1,0,1,0,0,                                         //ST6
                                0,0,1,0,1,1,0,0,1,  1,1,1,0,1,0,0,0,0,  1,0,0,1,1,0,1,0,0,  0,0,0,0,1,0,1,1,1, //STK4
                                1,1,1,0,1,1,0,0,0,  0,1,1,0,1,1,0,0,1,  1,1,1,1,1,0,0,0,0,  1,1,0,1,1,0,1,0,0, //STK6
                                1,0,0,1,1,0,1,1,0,  0,0,0,1,1,0,1,1,1,  0,0,0,0,1,1,1,1,1,  0,0,1,0,1,1,0,1,1,
                                1,1,1,0,1,1,0,0,1,  1,1,1,1,1,0,1,0,0,  1,0,0,1,1,0,1,1,1,  0,0,1,0,1,1,1,1,1, //STK7
                                0,1,1,0,1,1,0,1,1,  1,1,1,1,1,1,0,0,0,  1,1,0,1,1,0,1,1,0,  0,0,0,1,1,1,1,1,1, //STK8
                                1,1,1,0,1,1,0,1,1,  0,1,1,0,1,1,1,1,1,  1,1,1,1,1,1,1,0,0,  1,1,1,1,1,1,0,0,1, //STK9
                                1,1,1,1,1,0,1,1,0,  1,1,0,1,1,0,1,1,1,  1,0,0,1,1,1,1,1,1,  0,0,1,1,1,1,1,1,1,
                                1,1,1,0,1,1,1,1,1,  1,1,1,1,1,1,1,0,1,  1,1,1,1,1,0,1,1,1,  1,0,1,1,1,1,1,1,1, //STK10
                                0,1,0,0,1,1,0,0,0,  0,1,0,1,1,0,0,0,0,  0,0,0,1,1,0,0,1,0,  0,0,0,0,1,1,0,1,0, //TK4
                                1,1,1,1,1,1,0,1,1,  1,1,1,1,1,1,1,1,0,  1,1,0,1,1,1,1,1,1,  0,1,1,1,1,1,1,1,1};//K11
    
    int uncPatternST[65][9] = {0,0,1,0,1,0,0,0,0,  1,0,0,0,1,0,0,0,0,  0,0,0,0,1,0,0,1,0,  0,0,0,0,1,1,0,0,0, //Spur
                                0,0,1,0,1,1,0,0,0,  0,1,1,0,1,0,0,0,0,  1,1,0,0,1,0,0,0,0,  1,0,0,1,1,0,0,0,0, //L Cluster
                                0,0,0,1,1,0,1,0,0,  0,0,0,0,1,0,1,1,0,  0,0,0,0,1,0,0,1,1,  0,0,0,0,1,1,0,0,1,
                                0,1,1,1,1,0,0,0,0,  1,1,0,0,1,1,0,0,0,  0,1,0,0,1,1,0,0,1,  0,0,1,0,1,1,0,1,0, //4-Connected offset
        /*A=1,B=1*/             0,1,1,0,1,1,1,0,0,  1,1,0,1,1,0,0,0,1,  0,0,1,1,1,0,1,1,0,  1,0,0,0,1,1,0,1,1, //Spur corner cluster
        /*A=1,B=0*/             0,1,1,0,1,0,1,0,0,  1,0,0,1,1,0,0,0,1,  0,0,1,1,1,0,1,0,0,  1,0,0,0,1,0,0,1,1,
        /*A=0,B=1*/             0,0,1,0,1,1,1,0,0,  1,1,0,0,1,0,0,0,1,  0,0,1,0,1,0,1,1,0,  1,0,0,0,1,1,0,0,1,
        /*D=0*/                 1,1,0,1,1,0,0,0,0,                                                             //Corner cluster
        /*D=0*/                 0,1,0,1,1,1,0,0,0,  0,1,0,1,1,1,0,0,0,  0,0,0,1,1,1,0,1,0,  0,0,0,1,1,1,0,1,0, //Tee branch
                                0,1,0,1,1,0,0,1,0,  0,1,0,1,1,0,0,1,0,  0,1,0,0,1,1,0,1,0,  0,1,0,0,1,1,0,1,0,
        /*A=1,B=1,C=1,D=0*/     1,0,1,0,1,0,1,1,1,  1,0,1,0,1,1,1,0,1,  1,1,1,0,1,0,1,0,1,  1,0,1,1,1,0,1,0,1, //Vee Branch
        /*A=1,B=1,C=0,D=0*/     1,0,1,0,1,0,1,1,0,  1,0,0,0,1,1,1,0,1,  0,1,1,0,1,0,1,0,1,  1,0,1,1,1,0,0,0,1,
        /*A=1,B=0,C=1,D=0*/     1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,
        /*A=1,B=0,C=0,D=0*/     1,0,1,0,1,0,1,0,0,  1,0,0,0,1,0,1,0,1,  0,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,0,0,1,
        /*A=0,B=1,C=1,D=0*/     1,0,1,0,1,0,0,1,1,  1,0,1,0,1,1,1,0,0,  1,1,0,0,1,0,1,0,1,  0,0,1,1,1,0,1,0,1,
        /*A=0,B=1,C=0,D=0*/     1,0,1,0,1,0,0,1,0,  1,0,0,0,1,1,1,0,0,  0,1,0,0,1,0,1,0,1,  0,0,1,1,1,0,0,0,1,
        /*D=0*/                 0,1,0,0,1,1,1,0,0,  0,1,0,1,1,0,0,0,1,  0,0,1,1,1,0,0,1,0,  1,0,0,0,1,1,0,1,0}; //Diagonal Branch
    

    int uncPatternK[50][9] =   {0,0,0,0,1,0,0,0,1,  0,0,0,0,1,0,1,0,0,  0,0,1,0,1,0,0,0,0,  1,0,0,0,1,0,0,0,0, //Spur
                                0,0,0,0,1,0,0,1,0,  0,0,0,0,1,1,0,0,0,  0,0,0,1,1,0,0,0,0,  0,1,0,0,1,0,0,0,0, //Single 4-connection
                                0,1,0,0,1,1,0,0,0,  0,1,0,1,1,0,0,0,0,  0,0,0,0,1,1,0,1,0,  0,0,0,1,1,0,0,1,0, //L corner
        /*D=0*/                 1,1,0,1,1,0,0,0,0,  0,0,0,0,1,1,0,1,1,                                         //Corner cluster
        /*D=0*/                 0,1,0,1,1,1,0,0,0,  0,1,0,1,1,0,0,1,0,  0,0,0,1,1,1,0,1,0,  0,1,0,0,1,1,0,1,0, //Tee branch
        /*A=1,B=1,C=1,D=0*/     1,0,1,0,1,0,1,1,1,  1,0,1,0,1,1,1,0,1,  1,1,1,0,1,0,1,0,1,  1,0,1,1,1,0,1,0,1, //Vee Branch
        /*A=1,B=1,C=0,D=0*/     1,0,1,0,1,0,1,1,0,  1,0,0,0,1,1,1,0,1,  0,1,1,0,1,0,1,0,1,  1,0,1,1,1,0,0,0,1,
        /*A=1,B=0,C=1,D=0*/     1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,1,0,1,
        /*A=1,B=0,C=0,D=0*/     1,0,1,0,1,0,1,0,0,  1,0,0,0,1,0,1,0,1,  0,0,1,0,1,0,1,0,1,  1,0,1,0,1,0,0,0,1,
        /*A=0,B=1,C=1,D=0*/     1,0,1,0,1,0,0,1,1,  1,0,1,0,1,1,1,0,0,  1,1,0,0,1,0,1,0,1,  0,0,1,1,1,0,1,0,1,
        /*A=0,B=1,C=0,D=0*/     1,0,1,0,1,0,0,1,0,  1,0,0,0,1,1,1,0,0,  0,1,0,0,1,0,1,0,1,  0,0,1,1,1,0,0,0,1,
        /*A=0,B=0,C=1,D=0*/     1,0,1,0,1,0,0,0,1,  1,0,1,0,1,0,1,0,0,  1,0,0,0,1,0,1,0,1,  0,0,1,0,1,0,1,0,1,
        /*D=0*/                 0,1,0,0,1,1,1,0,0,  0,1,0,1,1,0,0,0,1,  0,0,1,1,1,0,0,1,0,  1,0,0,0,1,1,0,1,0}; //Diagonal Branch
    
    
    //Check patterns
    int total;
    int stackTemp[9];
    if (method=="Conditional"){
        
        if(type == "Shrinking"){
            for(int i = 0; i<58; i++){
                total = 0;
                for(int j=0; j<9; j++){
                    if (255*condPattern[i][j] == stack[j]) total++;
                }
                if (total == 9) return 255; //if theres a HIT
            }
            
        }
            
        else if (type == "Thinning"){
            for(int i = 16; i<62; i++){
                total = 0;
                for(int j=0; j<9; j++){
                    if (255*condPattern[i][j] == stack[j]) total++;
                }
                
                if (total == 9) return 255; //if theres a HIT
            }
        
        }
        
        else{ //Type = Skeletonizing
            for(int i = 26; i<66; i++){
                total = 0;
                for(int j=0; j<9; j++){
                    if (255*condPattern[i][j] == stack[j]) total++;
                }
                if (total == 9) return 255; //if theres a HIT
            }
        }
    }
    
    else if(method == "Unconditional"){
        if(type == "Shrinking" || type == "Thinning"){
            for(int i = 0; i<65; i++){
                if(i>=28){ //ignore the values of D (0 or 1)
                    for(int j=0; j<9; j++){
                        stackTemp[j] = stack[j];
                        stack[j] &= uncPatternST[i][j];
                        stack[j] *= 255;
                    }
                }

                total = 0;
                for(int j=0; j<9; j++){
                    if (255*uncPatternST[i][j] == stack[j]) total++;
                    if(i>=28) stack[j]=stackTemp[j];
                }
                
                if (total ==9) return 255; //if theres a HIT
            }
        }
        
        else{
            for(int i = 0; i<50; i++){
                if(i>=12){ //ignore the values of D (0 or 1)
                    for(int j=0; j<9; j++){
                        stackTemp[j] = stack[j];
                        stack[j] &= uncPatternK[i][j];
                        stack[j] *= 255;
                    }
                }
                
                total = 0;
                for(int j=0; j<9; j++){
                    if (255*uncPatternK[i][j] == stack[j]) total++;
                    if(i>=12) stack[j]=stackTemp[j];
                }
                
                if (total ==9) return 255; //if theres a HIT
            }
        }
    
    }
    
    return 0;
}

void morphological(ImageInfo image,string method,std::string folder){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],IN_FOLDER);

    unsigned char imageF[image.ImageSizeRows+2][image.ImageSizeCols+2];
    unsigned char imageG[image.ImageSizeRows+2][image.ImageSizeCols+2];
    
    // Array to store after the first stage
    unsigned char imageM[image.ImageSizeRows+2][image.ImageSizeCols+2];

    // Increase size
    for(int i=0; i<image.ImageSizeRows+2; i++){
        for(int j=0; j<image.ImageSizeCols+2; j++){
            imageM[i][j] = 0;
            imageG[i][j] = 0;
            imageF[i][j] = 0;
            if (i>0 && i<image.ImageSizeRows+1 && j>0 && j<image.ImageSizeCols+1)
                imageF[i][j] = imageData[i-1][j-1];
        }
    }
    int counter, frequency = 1,sum,squares=0;
    int stack[9],squareF[11];
    squareF[0] = 0;
    string flag = "GO";
    
    //Repeat until we reach a steady state
    while(flag == "GO"){
        squares = 0;
        //FIRST PHASE
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                
                if(imageF[i][j]==255){ //Check if image is a hit or not
                    counter = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            stack[counter] = imageF[i+n][j+m];
                            counter++;
                        }
                    }
                    
                    imageM[i][j] = checkMarkPattern(stack,method,"Conditional");
                    
                    if(image.ImageName == "squares.raw"){
                        sum = 0;
                        for(int m=0;m<9;m++){
                            sum += stack[m];
                        }
                        if(sum==255){//Means theres only one pixel
                            squares++;
                        }
                        squareF[frequency]=squares;
                    }
                }
            }
        }
        
        //SECOND PHASE
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                
                if(imageF[i][j]==255){ //Check if image is a hit or not
                    
                    if(imageM[i][j] == 0)
                        imageG[i][j] = imageF[i][j]; //Do nothing
                    
                    else{
                        counter = 0;
                        for(int n=-1;n<=1;n++){
                            for(int m=-1;m<=1;m++){
                                stack[counter] = imageM[i+n][j+m];
                                counter++;
                            }
                        }
                        imageG[i][j] = checkMarkPattern(stack,method,"Unconditional");
                        
                    }
                }
            }
        }
    
        flag = "STOP";
        //Check if we have reached a steady state
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                if(imageF[i][j]!=imageG[i][j]) flag = "GO";
                imageM[i][j] = 0;
                imageF[i][j] = imageG[i][j];//To repeat the process
            }
        }
        
        frequency++;
    }
    
    //For square.raw
    if(image.ImageName=="squares.raw"){

        ofstream SQUA(OUT_FOLDER+"squares.txt");
        SQUA.is_open();
        
        SQUA << "\nSQUARES LOG\n";
        SQUA << "\nTotal number of squares: " << squares <<endl <<endl;
        for(int i=0;i<10;i++){
            SQUA << "Number of iterations: " << i << ", Number of squares: " << squareF[i+1]-squareF[i];
            
            if (i==0) SQUA << ", with a Size of: " << i+1 << "x" << i+1 <<endl;
            else SQUA << ", with a Size of: " << 2*i << "x" << 2*i <<endl;
        }
        
        SQUA.close();
    }
    
    
    //Fix to correct size
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    
    for(int i=1; i<image.ImageSizeRows+1; i++){
        for(int j=1; j<image.ImageSizeCols+1; j++){
            imageOut[i-1][j-1] = imageG[i][j];
        }
    }
    
    if(folder!= "both"){
        //Writes files in the inputs folder
        output = folder + input + "_" + method + ".raw";
    
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
        writeImage(result,&imageOut[0][0]);
    }
    
    else{ //Save file in IN and OUT folder
        //Writes files in the inputs folder
        output = IN_FOLDER + input + "_" + method + ".raw";
        
        //Write image into a new raw file
        ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
        writeImage(result,&imageOut[0][0]);
        
        //Writes files in the inputs folder
        output = OUT_FOLDER + input + "_" + method + ".raw";
        
        //Write image into a new raw file
        ImageInfo result2(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
        writeImage(result2,&imageOut[0][0]);
        
    }
}


void myDilation(ImageInfo image, std::string folder,int iterations){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);

    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],IN_FOLDER);
    
    unsigned char imageF[image.ImageSizeRows+2][image.ImageSizeCols+2];
    unsigned char temp[image.ImageSizeRows+2][image.ImageSizeCols+2];
    
    // Increase size
    for(int i=0; i<image.ImageSizeRows+2; i++){
        for(int j=0; j<image.ImageSizeCols+2; j++){
            if (i>0 && i<image.ImageSizeRows+1 && j>0 && j<image.ImageSizeCols+1)
                imageF[i][j] = imageData[i-1][j-1];
        }
    }
    
    int mask[9] = {0,1,0,1,0,1,0,1,0};
    int counter,sum;
    int repeat=0;
    
    while(repeat<iterations){
        //Perform dilation
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                
                temp[i][j] = 0;
                if(imageF[i][j]==255){ //Check if image is a hit or not
                    sum = 0;
                    counter = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            if((imageF[i+n][j+m]&mask[counter]) != 1){ //If it cant be removed
                                temp[i+n][j+m] = 255;
                            }
                            counter++;
                        }
                    }
                }
            }
        }
        
        //Set parameters for next iteration
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                imageF[i][j] = temp[i][j];
                temp[i][j] = 0;
            }
        }
        repeat++;
    }
    
    
    //Fix to correct size
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    for(int i=1; i<image.ImageSizeRows+1; i++){
        for(int j=1; j<image.ImageSizeCols+1; j++){
            imageOut[i-1][j-1] = imageF[i][j];
        }
    }
    
    //Writes files in the inputs folder
    output = folder + "temp.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageOut[0][0]);

}


void myErosion(ImageInfo image, std::string folder_in,std::string folder_out,int iterations){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],folder_in);
    
    unsigned char imageF[image.ImageSizeRows+2][image.ImageSizeCols+2];
    unsigned char temp[image.ImageSizeRows+2][image.ImageSizeCols+2];
    
    // Increase size
    for(int i=0; i<image.ImageSizeRows+2; i++){
        for(int j=0; j<image.ImageSizeCols+2; j++){
            if (i>0 && i<image.ImageSizeRows+1 && j>0 && j<image.ImageSizeCols+1)
                imageF[i][j] = imageData[i-1][j-1];
        }
    }
    
    int mask[9] = {0,1,0,1,0,1,0,1,0};
    int counter,sum;
    int repeat=0;
    
    while(repeat<iterations){
        //Perform dilation
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                
                temp[i][j] = 0;
                if(imageF[i][j]==255){ //Check if image is a hit or not
                    sum = 0;
                    counter = 0;
                    for(int n=-1;n<=1;n++){
                        for(int m=-1;m<=1;m++){
                            sum +=imageF[i+n][j+m]&mask[counter];
                            counter++;
                        }
                    }
                    
                    if(sum==4){ //If it cant be removed
                        temp[i][j] = 255;
                    }
                    else
                        temp[i][j] = 0;
                }
            }
        }
        
        //Set parameters for next iteration
        for(int i=1; i<image.ImageSizeRows+1; i++){
            for(int j=1; j<image.ImageSizeCols+1; j++){
                imageF[i][j] = temp[i][j];
                temp[i][j] = 0;
            }
        }
        repeat++;
    }
    
    
    //Fix to correct size
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    for(int i=1; i<image.ImageSizeRows+1; i++){
        for(int j=1; j<image.ImageSizeCols+1; j++){
            imageOut[i-1][j-1] = imageF[i][j];
        }
    }
    
    //Writes files in the inputs folder
    output = folder_out + "temp.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageOut[0][0]);
}

int findHoles(ImageInfo image,int *positions){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    
    readImage(image,&imageData[0][0],IN_FOLDER);
    
    //Initialize to zero and flip values
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            imageData[i][j] = 255-imageData[i][j];
        }
    }
    
    //Writes files in the inputs folder
    output = IN_FOLDER + "temp.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageData[0][0]);
    
    //Shrink the inverse of the image
    image.ImageName = "temp.raw";
    morphological(image,"Shrinking","both");
    image.ImageName = "temp_Shrinking.raw";
    readImage(image,&imageData[0][0],IN_FOLDER);

    //Remove unnecessary files
    remove("Inputs/temp_Shrinking.raw");
    remove("Outputs/temp_Shrinking.raw");
    remove("Inputs/temp.raw");
    remove("Outputs/temp.raw");
    
    int holes=0;
    int sum,counter;
    
    //Find quantity of holes and position
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            if(imageData[i][j]==255){ //Possible single white pixel
                sum = 0;
                counter = 0;
                for(int n=-1;n<=1;n++){
                    for(int m=-1;m<=1;m++){
                        sum +=imageData[i+n][j+m];
                        counter++;
                    }
                }
                
                if(sum==255){ //Only the center one is ON
                    positions[2*holes] = i;
                    positions[2*holes+1] = j;
                    holes++;
                }
            }
        }
    }
    
    return holes;
}

void fillHoles(ImageInfo image, int *points, int holes){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    unsigned char imageTemp[image.ImageSizeRows][image.ImageSizeCols];
    unsigned char imageTemp2[image.ImageSizeRows][image.ImageSizeCols];
    unsigned char imageComp[image.ImageSizeRows][image.ImageSizeCols];
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];
    
    readImage(image,&imageData[0][0],IN_FOLDER);
    int repeat = 0;
    int row,col;
    
    //Initialize to zero
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            imageTemp[i][j] = 0;
            imageTemp2[i][j] = 0;
            imageOut[i][j] = 0;
            imageComp[i][j] = 255-imageData[i][j];
        }
    }
    
    int B[9] = {0,1,0,1,0,1,0,1,0};
    int counter;
    
    while(repeat<holes){
        row = points[2*repeat];
        col = points[2*repeat+1];
        
        //Initial internal point
        imageTemp[row][col] = 255;
    
        string flag = "GO";
        
        while(flag == "GO"){
            for(int i=0; i<image.ImageSizeRows; i++){
                for(int j=0; j<image.ImageSizeCols; j++){
                    imageTemp2[i][j] = imageTemp[i][j]; //Storing previous X
                }
            }
            
            for(int i=0; i<image.ImageSizeRows; i++){
                for(int j=0; j<image.ImageSizeCols; j++){
                    
                    if(imageTemp2[i][j]==255){
                        counter = 0;
                        //Check the neighborhood
                        for(int n=-1;n<=1;n++){
                            for(int m=-1;m<=1;m++){
                                if(imageTemp[i+n][j+m]!=255*B[counter]){ //XOR
                                    imageTemp[i+n][j+m] = 255;
                                }
                                counter++;
                            }
                        }
                    }
                }
            }

            flag ="STOP";
            //X n A^c and check if we have reached convergence
            for(int i=0; i<image.ImageSizeRows; i++){
                for(int j=0; j<image.ImageSizeCols; j++){
                    imageTemp[i][j] &= imageComp[i][j];
                    if(imageTemp[i][j]!=imageTemp2[i][j]) flag = "GO";
                }
            }
        }
        
        //Final step: Xconv u A
        for(int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                imageTemp[i][j] = imageTemp[i][j]|imageData[i][j];
                imageOut[i][j] |= imageTemp[i][j];
                imageTemp[i][j] = 0;
            }
        }
        
        repeat++;
    }
    
    
    //Writes files in the inputs folder
    output = OUT_FOLDER + input + "NoHoles.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageOut[0][0]);
    
    
    output = IN_FOLDER + input + "NoHoles.raw";
    
    //Write image into a new raw file in the outputs folder
    result.ImageName = output;
    writeImage(result,&imageOut[0][0]);
    
}


int countLonelyPixels(ImageInfo image,int *pos,std::string folder){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    int pixels = 0,sum,counter;
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],folder);
    
    //Initialize to zero and flip values
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            
            if(imageData[i][j]==255){ //Check if image is a hit or not
                sum = 0;
                counter = 0;
                for(int n=-1;n<=1;n++){
                    for(int m=-1;m<=1;m++){
                        sum +=imageData[i+n][j+m];
                        counter++;
                    }
                }
                //Check if theres only one pixel in the neighborhood
                if(sum == 255) {
                    pos[2*pixels] = i;
                    pos[2*pixels+1] = j;
                    pixels++;
                }
            }
        }
    }
    
    return pixels;
}

void fixSquares(ImageInfo image, std::string folder){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    int sum,counter;
    
    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],folder);
    
    int mask[4][25] = {0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1, //Top Left
                       0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0, //Top Right
                       0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0, //Bottom Left
                       1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0};//Bottom Right
    
    //Initialize to zero and flip values
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            
            if(imageData[i][j]==255){ //Check if image is a hit or not

                for(int k=0;k<4;k++){
                    counter = 0;
                    sum = 0;
                    for(int n=-2;n<=2;n++){
                        for(int m=-2;m<=2;m++){
                            if(255*mask[k][counter]==imageData[i+n][j+m])
                                sum +=1;
                            counter++;
                        }
                    }
                    //Fix edges
                    if(k==0 && sum==25) imageData[i-1][j-1] = 255;
                    else if(k==1 && sum==25) imageData[i-1][j+1] = 255;
                    else if(k==2 && sum==25) imageData[i+1][j-1] = 255;
                    else if(k==3 && sum==25) imageData[i+1][j+1] = 255;
                }
            }
        }
    }
    
    output = OUT_FOLDER + input + "Fixed.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageData[0][0]);
    
}


void checkCircularity(ImageInfo image, int *pos,int objects,std::string folder_read, std::string folder_write,int holes){
    std::string output;
    std::string location = image.ImageName;
    std::string input = location.substr(0,location.length()-4);
    int counter = 0;
    double circularity,area = 0,perimeter;

    // Read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],folder_read);
    
    ofstream circ(OUT_FOLDER+"countinggame.txt");
    circ.is_open();
    circ << "COUNTING GAME" << endl << endl;
    
    circ << "There are " << holes << " holes within white objects in the image\n\n"
         << "There are " << objects << " white objects in the image\n\n";
    
    //Setting up variables
    string flag;
    int wide,center_i,center_j,circles=0,squares=0,sum,add;
    int radius=0;
    double area2,ratio;
    
    while(counter<objects){
        wide = 1,perimeter=0;
        flag = "GO";
        center_i = pos[2*counter];
        center_j = pos[2*counter+1];
        
        while(flag == "GO"){
            area = 0;sum=0;
            //check boxes
            for(int i=-wide;i<=wide;i++){
                for(int j=-wide;j<=wide;j++){
                    if(imageData[i+center_i][j+center_j]) area++;
                    
                    //Check edges
                    if(i==-wide||i==wide) sum+= imageData[i+center_i][j+center_j];
                    if(j==-wide||j==wide) sum+= imageData[i+center_i][j+center_j];
                }
            }
            //Has boxed the whole image in and the edged are all black
            if(sum==0) flag = "STOP";
            wide++;
        }
    
        //Find perimeter
        for(int i=-wide;i<=wide;i++){
            for(int j=-wide;j<=wide;j++){
                //Check only nonzero pixels
                if(imageData[i+center_i][j+center_j]!=0){
                    add = 0;
                    //Check 4-connect neighborhood
                    if(imageData[i+center_i-1][j+center_j]==0) add++;
                    if(imageData[i+center_i+1][j+center_j]==0) add++;
                    if(imageData[i+center_i][j+center_j-1]==0) add++;
                    if(imageData[i+center_i][j+center_j+1]==0) add++;
                    
                    perimeter +=add;
                }
            }
        }
        
        //Find circulariry of object
        circularity = (4*PI*area)/(perimeter*perimeter);
        counter++;
        
        //Output data to file
        circ << "Object " << counter << " has an area of " << area << ", and a perimeter of " << perimeter << endl
             << "And a circularity of " << circularity << endl;
        
        if (circularity>0.85 && circularity<=1.15){
            circ << "Object's shape is a circle" << endl << endl;
            circles++;
        }
        
        if(circularity>0.77 && circularity<=0.79){
            circ << "Object's shape is a square" << endl;
            squares++;
        }
        else{
            circ << "Object's shape is unknown" << endl;
        }
        
        
        //Check for circles by looking at its area given the radius (obtaining from wide)
        radius = wide - 2;
        area2 = PI*radius*radius;
        ratio = area/area2;
        if(ratio>0.8 && ratio < 1.02){
            circ << "Computed area over expected pi*R^2 area " << ratio << ", possible shape from area: circle" <<endl<<endl;
            circles++;
        }
        else{
            circ << "Computed area over expected area " << ratio << ", possible shape from area: not a circle" <<endl<<endl;
        }

        
    }
    
    circ << endl << "-> The total number of circles in the image is: " << circles << endl
         << "-> The total number of squares in the image is: " << squares << endl;
    
    circ.close();

}
