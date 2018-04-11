//-----------------------------
//  EE 569 Assignment 2
//  Date: 02/14/17
//  Name: Leila Suasnabar
//  ID: 3109-9816-56
//  email: lsuasnab@usc.edu
//-----------------------------

#ifndef myFunctions_h
#define myFunctions_h

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

const std::string IN_FOLDER = "Inputs/";
const std::string OUT_FOLDER = "Outputs/";

struct ImageInfo{
    
    // Variables
    int BytesPerPixel;
    int ImageSizeCols;
    int ImageSizeRows;
    std::string ImageName;
    
    //Constructors
    ImageInfo();
    ImageInfo(int bytes, int sizeCols, int sizeRows, std::string name);
    
};

void readImage(ImageInfo,unsigned char *,std::string folder);
void writeImage(ImageInfo,unsigned char *);
void datatotext(float *,std::string, int);

// Problem 1
void doAffineWarping(ImageInfo);
void doWarping(ImageInfo);
void solvePuzzle(ImageInfo,ImageInfo,ImageInfo);
void bilinear(ImageInfo,double,double,std::string);
void homographicTran(ImageInfo,ImageInfo);


// Problem 2
void dithering(ImageInfo,int);
void dithering4(ImageInfo,int);
void expandImage(ImageInfo,int);
void errorDifussion(ImageInfo,std::string);
// Problem 3
void morphological(ImageInfo,std::string,std::string);
int checkMarkPattern(int*,std::string,std::string);
int findHoles(ImageInfo,int*);
void fillHoles(ImageInfo,int*,int);
int countLonelyPixels(ImageInfo,int*,std::string);
void fixSquares(ImageInfo, std::string);
void myErosion(ImageInfo, std::string,std::string,int);
void myDilation(ImageInfo, std::string,int);
void countSquares(ImageInfo,std::string);
void checkCircularity(ImageInfo, int*,int,std::string, std::string,int);

#endif /* myFunctions_h */
