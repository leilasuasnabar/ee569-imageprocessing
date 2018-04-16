//-----------------------------
//  EE 569 Assignment 3
//  Date: 03/20/17
//  Name: Leila Suasnabar
//  ID: 3109-9816-56
//  email: lsuasnab@usc.edu
//-----------------------------

#ifndef myFunctions_h
#define myFunctions_h

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"


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

void readImage(ImageInfo,unsigned char *,std::string);
void writeImage(ImageInfo,unsigned char *,std::string);
void datatotext(float *,std::string, int);
void toGrayscale(ImageInfo, std::string,std::string);
void expandImage(ImageInfo, int,std::string);

// Problem 1
void classifyTex(ImageInfo,std::string,int,int);
void outerProduct(int*,int*,int*);
void findLabels(cv::Mat,cv::Mat,std::string,int*,int*);
void findLabels2(cv::Mat,int,int*);
void findSegmentation(ImageInfo,int,int,std::string,int);

//Problem 2
void cannyEdgeDetector(ImageInfo,double,double);
void removeBlob(ImageInfo,int);
void evaluation(ImageInfo,std::string,int,std::string*,int,std::string);



#endif /* myFunctions_h */







