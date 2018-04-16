//-----------------------------
//  EE 569 Assignment 3
//  Date: 03/20/17
//  Name: Leila Suasnabar
//  ID: 3109-9816-56
//  email: lsuasnab@usc.edu
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
using namespace cv;

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

void readImage(ImageInfo image, unsigned char *imageData,std::string read_from_folder){
    //Retrieve information from image
    int bytes = image.BytesPerPixel;
    int cols = image.ImageSizeCols;
    int rows = image.ImageSizeRows;
    std::string name = read_from_folder + image.ImageName;
    
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

void writeImage(ImageInfo image,unsigned char *imageData, std::string write_to_folder){
    //Retrieve information from image
    int bytes = image.BytesPerPixel;
    int cols = image.ImageSizeCols;
    int rows = image.ImageSizeRows;
    std::string name = write_to_folder + image.ImageName;
    
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

void toGrayscale(ImageInfo image, std::string output,std::string folder){
    std::string location = image.ImageName;
    
    // Allocate image data array and read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],IN_FOLDER);
    
    // Gray scaled images
    unsigned char imageD[image.ImageSizeRows][image.ImageSizeCols];
    
    for(int i=0; i<image.ImageSizeRows ;i++){
        for(int j =0; j<image.ImageSizeCols ;j++){
            imageD[i][j] = 0.21*imageData[i][j][0] + 0.72*imageData[i][j][1] + 0.07*imageData[i][j][2];
        }
    }
    
    //Writes files in the inputs folder
    output = folder + output;
    
    //Write image into a new raw file
    ImageInfo result(1,image.ImageSizeRows,image.ImageSizeCols,output);
    writeImage(result,&imageD[0][0],IN_FOLDER);
    
}

void expandImage(ImageInfo image, int window, string readFrom){
    
    std::string location = image.ImageName;
    std::string output;
    
    window = (window-1)/2; //extra rows/cols needed
    
    // Allocate image data array and read image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],readFrom);
    
    // Allocate image data array for extended image
    unsigned char imageExt[image.ImageSizeRows+2*window]
    [image.ImageSizeCols+2*window][image.BytesPerPixel];
    
    for(int k=0; k<image.BytesPerPixel; k++){
        
        for(int j=0; j<image.ImageSizeRows+2*window ;j++){
            for(int i=0; i<image.ImageSizeCols+2*window;i++){
                imageExt[j][i][k] = 0;
            }
        }
        
        
        //Add image to the center
        for(int i=0; i<image.ImageSizeRows ;i++){
            for(int j=0; j<image.ImageSizeCols ;j++){
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
    output = "imageExpanded.raw";
    
    //Write image into a new raw file
    ImageInfo result(image.BytesPerPixel,image.ImageSizeRows+2*window,image.ImageSizeCols+2*window,output);
    writeImage(result,&imageExt[0][0][0],IN_FOLDER);
    
}

void outerProduct(int* A,int* B, int*output){

    int counter = 0;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            output[counter] = A[i]*B[j];
            counter++;
        }
    }
}


void classifyTex(ImageInfo image, std::string name, int train, int test){

    //Setting up the Laws Filters
    int laws[25][25] = {1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1,         //L5L5
                       -1,-2,0,2,1,-4,-8,0,8,4,-6,-12,0,12,6,-4,-8,0,8,4,-1,-2,0,2,1,       //L5E5
                       -1,0,2,0,-1,-4,0,8,0,-4,-6,0,12,0,-6,-4,0,8,0,-4,-1,0,2,0,-1,        //L5S5
                       -1,2,0,-2,1,-4,8,0,-8,4,-6,12,0,-12,6,-4,8,0,-8,4,-1,2,0,-2,1,       //L5W5
                       1,-4,6,-4,1,4,-16,24,-16,4,6,-24,36,-24,6,4,-16,24,-16,4,1,-4,6,-4,1,//L5R5
                       -1,-4,-6,-4,-1,-2,-8,-12,-8,-2,0,0,0,0,0,2,8,12,8,2,1,4,6,4,1,       //E5L5
                        1,2,0,-2,-1,2,4,0,-4,-2,0,0,0,0,0,-2,-4,0,4,2,-1,-2,0,2,1,          //E5E5
                        1,0,-2,0,1,2,0,-4,0,2,0,0,0,0,0,-2,0,4,0,-2,-1,0,2,0,-1,            //E5S5
                        1,-2,0,2,-1,2,-4,0,4,-2,0,0,0,0,0,-2,4,0,-4,2,-1,2,0,-2,1,          //E5W5
                       -1,4,-6,4,-1,-2,8,-12,8,-2,0,0,0,0,0,2,-8,12,-8,2,1,-4,6,-4,1,       //E5R5
                       -1,-4,-6,-4,-1,0,0,0,0,0,2,8,12,8,2,0,0,0,0,0,-1,-4,-6,-4,-1,        //S5L5
                        1,2,0,-2,-1,0,0,0,0,0,-2,-4,0,4,2,0,0,0,0,0,1,2,0,-2,-1,            //S5E5
                        1,0,-2,0,1,0,0,0,0,0,-2,0,4,0,-2,0,0,0,0,0,1,0,-2,0,1,              //S5S5
                        1,-2,0,2,-1,0,0,0,0,0,-2,4,0,-4,2,0,0,0,0,0,1,-2,0,2,-1,            //S5W5
                       -1,4,-6,4,-1,0,0,0,0,0,2,-8,12,-8,2,0,0,0,0,0,-1,4,-6,4,-1,          //S5R5
                       -1,-4,-6,-4,-1,2,8,12,8,2,0,0,0,0,0,-2,-8,-12,-8,-2,1,4,6,4,1,       //W5L5
                        1,2,0,-2,-1,-2,-4,0,4,2,0,0,0,0,0,2,4,0,-4,-2,-1,-2,0,2,1,          //W5E5
                        1,0,-2,0,1,-2,0,4,0,-2,0,0,0,0,0,2,0,-4,0,2,-1,0,2,0,-1,            //W5S5
                        1,-2,0,2,-1,-2,4,0,-4,2,0,0,0,0,0,2,-4,0,4,-2,-1,2,0,-2,1,          //W5W5
                       -1,4,-6,4,-1,2,-8,12,-8,2,0,0,0,0,0,-2,8,-12,8,-2,1,-4,6,-4,1,       //W5R5
                       1,4,6,4,1,-4,-16,-24,-16,-4,6,24,36,24,6,-4,-16,-24,-16,-4,1,4,6,4,1,//R5L5
                       -1,-2,0,2,1,4,8,0,-8,-4,-6,-12,0,12,6,4,8,0,-8,-4,-1,-2,0,2,1,       //R5E5
                       -1,0,2,0,-1,4,0,-8,0,4,-6,0,12,0,-6,4,0,-8,0,4,-1,0,2,0,-1,          //R5S5
                       -1,2,0,-2,1,4,-8,0,8,-4,-6,12,0,-12,6,4,-8,0,8,-4,-1,2,0,-2,1,       //R5W5
                      1,-4,6,-4,1,-4,16,-24,16,-4,6,-24,36,-24,6,-4,16,-24,16,-4,1,-4,6,-4,1};//R5R5

    //Output data to text file
    std::string output = OUT_FOLDER + "Problem 1A.txt";
    //To store file
    ofstream classi(output);
    classi << "\nTRAINING\n\n";
    
    //Array to store the average energies
    int energies[25][train];
    int counter = 0, lawsCounter = 0, boxCounter = 0;
    double sum = 0, energy = 0;
    double globalMean = 0;
    
    //Store the features
    Mat features(train,25,CV_32F);
    
    //Repeat procedure for each training image
    while(counter<train){
        
        image.ImageName = name +to_string(counter+1)+".raw";
        
        //Read file and allocate memory
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);
        
        //Create expanded image to be used with a filter window of size 5
        expandImage(image,5,IN_FOLDER);
        
        //Calculating the global mean
        for(int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                globalMean += imageData[i][j];
            }
        }
        globalMean /= (image.ImageSizeRows*image.ImageSizeRows);
        
        //Read expanded image
        unsigned char imageExp[image.ImageSizeRows+4][image.ImageSizeCols+4];
        ImageInfo imageE(1,image.ImageSizeCols+4,image.ImageSizeRows+4,"imageExpanded.raw");
        readImage(imageE,&imageExp[0][0],IN_FOLDER);
        
        //Variable to store positive and negative values
        double data[image.ImageSizeRows+4][image.ImageSizeCols+4];
        
        //Substract global mean from the expanded image
        for(int i=0; i<image.ImageSizeRows+4; i++){
            for(int j=0; j<image.ImageSizeCols+4; j++){
                data[i][j] = imageExp[i][j] - globalMean;
                imageData[i][j] = 0;
            }
        }
        
        lawsCounter = 0;
        classi << "Object #" << counter +1 << " features value: " << endl;
        //Pass the filters
        while(lawsCounter<25){
            
            features.at<float>(counter,lawsCounter) = 0;
            energy = 0;
            for(int i=2; i<image.ImageSizeRows+2; i++){
                for(int j=2; j<image.ImageSizeCols+2; j++){
                    
                    boxCounter = 0;
                    sum = 0;
                    for(int m=-2;m<=2;m++){
                        for(int n=-2;n<=2;n++){
                            sum +=  data[i+m][j+n]*laws[lawsCounter][boxCounter];
                            boxCounter++;
                        }
                    }
                    energy += abs(sum/25);
                }
            }
            energy /= (image.ImageSizeCols*image.ImageSizeRows); //find average energy
            energies[counter][lawsCounter]= energy;
            features.at<float>(counter,lawsCounter) = energy;
            classi << energy << endl;
            lawsCounter++;
        }
        globalMean = 0;
        counter++;
        classi << endl;
        
    }
    
    classi << "\n\nALL 25D features as a matrix\n" << features << endl << endl;
    //Find the 3D vector from the 25D vector using PCA
    Mat newFeatures;
    PCA pcaTrain(features,Mat(),CV_PCA_DATA_AS_ROW, 3);
    pcaTrain.project(features,newFeatures);
    
    classi << "All 3D features as a matrix\n" << newFeatures << endl << endl;
    
    classi << "\nTESTING\n\n";
    
    //Find the features of the test data
    Mat featuresTest(test,25,CV_32F);
    counter = 0;
    string letters[] = {"A","B","C","D","E","F"};
    
    //Repeat procedure for each training image
    while(counter<test){
        globalMean = 0;
        image.ImageName = name +letters[counter]+".raw";
        
        //Read file and allocate memory
        unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
        readImage(image,&imageData[0][0],IN_FOLDER);
        
        //Create expanded image to be used with a filter window of size 5
        expandImage(image,5,IN_FOLDER);
        
        //Calculating the global mean
        for(int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                globalMean += imageData[i][j];
            }
        }
        globalMean /= (image.ImageSizeRows*image.ImageSizeRows);
        
        //Read expanded image
        unsigned char imageExp[image.ImageSizeRows+4][image.ImageSizeCols+4];
        ImageInfo imageE(1,image.ImageSizeCols+4,image.ImageSizeRows+4,"imageExpanded.raw");
        readImage(imageE,&imageExp[0][0],IN_FOLDER);
        
        //Variable to store positive and negative values
        double data[image.ImageSizeRows+4][image.ImageSizeCols+4];
        
        //Substract global mean from the expanded image
        for(int i=0; i<image.ImageSizeRows+4; i++){
            for(int j=0; j<image.ImageSizeCols+4; j++){
                data[i][j] = imageExp[i][j] - globalMean;
                imageData[i][j] = 0;
            }
        }
        
        lawsCounter = 0;
        classi << "Object " << letters[counter] << " features value: " << endl;
        //Pass the filters
        while(lawsCounter<25){
            
            featuresTest.at<float>(counter,lawsCounter) = 0;
            energy = 0;
            for(int i=2; i<image.ImageSizeRows+2; i++){
                for(int j=2; j<image.ImageSizeCols+2; j++){
                    
                    boxCounter = 0;
                    sum = 0;
                    for(int m=-2;m<=2;m++){
                        for(int n=-2;n<=2;n++){
                            sum +=  (data[i+m][j+n]*laws[lawsCounter][boxCounter]);
                            boxCounter++;
                        }
                    }
                    energy += abs(sum/25);
                }
            }
            energy /= (image.ImageSizeCols*image.ImageSizeRows); //find average energy
            energies[counter][lawsCounter]= energy;
            featuresTest.at<float>(counter,lawsCounter) = energy;
            classi << energy << endl;
            lawsCounter++;
        }
        counter++;
        classi << endl;
        
    }

    classi << "\n\nALL 25D features as a matrix\n" << featuresTest << endl << endl;
    //Find the 3D vector from the 25D vector using PCA
    Mat newFeaturesTest;
    PCA pcaTest(featuresTest,Mat(),CV_PCA_DATA_AS_ROW, 3);
    pcaTest.project(featuresTest,newFeaturesTest);

    classi << "All 3D features as a matrix\n" << newFeaturesTest << endl << endl;
    

    //Dividing data into 4 clusters for both, unspervised and supervised method
    int labelTrain[train];
    int labelTest[test];

    //UNSUPERVISED METHOD
    //Applying k means clustering algorithm for 25D
    findLabels(features,featuresTest,"unsupervised",labelTrain,labelTest);
    
    classi << "\n\nLABELS\n\n" << "Method: unsupervised with 25D\n\n" << "Training data: \n";
    
    for(int i=0; i<train;i++){
        classi << "Feature "  << i+1 << ": " << labelTrain[i] << endl;
    }
    
    classi << "\nTesting data: \n";
    for(int i=0; i<test;i++){
        classi << "Feature "  << letters[i] << ": " << labelTest[i] << endl;
    }
    
    //Applying k means clustering algorithm for 3D
    findLabels(newFeatures,newFeaturesTest,"unsupervised",labelTrain,labelTest);
    classi << "\n\nLABELS\n\n" << "Method: unsupervised with 3D\n\n" << "Training data: \n";
    
    for(int i=0; i<train;i++){
        classi << "Feature "  << i+1 << ": " << labelTrain[i] << endl;
    }
    
    classi << "\nTesting data: \n";
    for(int i=0; i<test;i++){
        classi << "Feature "  << letters[i] << ": " << labelTest[i] << endl;
    }
    
    
    //SUPERVISED METHOD
    //Applying clustering algorithm for 25D
    findLabels(features,featuresTest,"supervised",labelTrain,labelTest);
    classi << "\n\nLABELS\n\n" << "Method: supervised with 25D\n\n" << "Training data: \n";
    
    for(int i=0; i<train;i++){
        classi << "Feature "  << i+1 << ": " << labelTrain[i] << endl;
    }
    
    classi << "\nTesting data: \n";
    for(int i=0; i<test;i++){
        classi << "Feature "  << letters[i] << ": " << labelTest[i] << endl;
    }
    
    //Applying clustering algorithm for 3D
    findLabels(newFeatures,newFeaturesTest,"supervised",labelTrain,labelTest);
    classi << "\n\nLABELS\n\n" << "Method: supervised with 3D\n\n" << "Training data: \n";
    
    for(int i=0; i<train;i++){
        classi << "Feature "  << i+1 << ": " << labelTrain[i] << endl;
    }
    
    classi << "\nTesting data: \n";
    for(int i=0; i<test;i++){
        classi << "Feature "  << letters[i] << ": " << labelTest[i] << endl;
    }
    
    classi.close();
}


void findLabels(Mat dataTrain, Mat dataTest, string method,int *label, int *labelTest){
    int objects = dataTrain.rows;
    int features = dataTrain.cols;
    double sum=0, mean[features],std[features];

    //To store final 4 centroids
    double c1[features],c2[features],c3[features],c4[features];
    
    if(method == "unsupervised"){//unsupervised method a.k.a. using k-means algorithm
        for(int i=0; i<features; i++){
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += dataTrain.at<float>(j,i);
            }
            mean[i] = sum/objects;
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += pow(dataTrain.at<float>(j,i) - mean[i],2);
            }
            std[i] = sqrt(sum/objects);
        }
        
        //temp centroids
        //double c1[features],c2[features],c3[features],c4[features];
        for(int i=0; i<25;i++){
            c1[i] = mean[i] - std[i];
            c2[i] = mean[i] + std[i];
        }
        
        //Find temp label using euclidean distance
        double dist1, dist2, dist3, dist4, tempLabel[objects];
        bool check = true;
        
        for(int i=0;i<objects;i++){
            label[i] = 0;
        }
        
        while(check){ //Check cluster of 2
            sum = 0;
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0;dist2 = 0;

                //cout << "centers:" << c1[i] << ", " << c2[i] << endl;
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                //cout << "dist: " << dist1 << ", " << dist2 << endl;
                
                //Compare distances
                if(dist1<dist2) label[i] = 1;
                else    label[i] = 2;
                
                //cout << label[i] << endl;
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
                //cout << label[i] << ", " << tempLabel[i] << ", " << sum << endl;
            }

            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2;
                int counter;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0;
                    counter = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1) sum1 += dataTrain.at<float>(j,i);
                        else{
                            sum2 += dataTrain.at<float>(j,i);
                            counter++;
                        }
                    }
                    c1[i] = sum1/(objects-counter);
                    c2[i] = sum2/counter;
                    //cout << "computed:" << c1[i] << ", " << c2[i] << endl;
                }
                //cout << endl << endl;
            }
        }
        
        //New mat containing 2 clusters to be used to find 4 clusters
        Mat A,B;
        //Find new label using euclidean distance
        double mean1[features],mean2[features],std1[features],std2[features];
        check = true; //flag
        
        //Find temporary centroids for 4 clusters
        for(int i=0; i<objects;i++){
            if(tempLabel[i]==1) A.push_back(dataTrain.row(i));
            else B.push_back(dataTrain.row(i));
        }

        for(int i=0; i<A.cols; i++){
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += A.at<float>(j,i);
            }
            mean1[i] = sum/A.rows;
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += pow(A.at<float>(j,i) - mean1[i],2);
            }
            std1[i] = sqrt(sum/A.rows);
        }
        
        
        for(int i=0; i<B.cols; i++){
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += B.at<float>(j,i);
            }
            mean2[i] = sum/B.rows;
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += pow(B.at<float>(j,i) - mean2[i],2);
            }
            std2[i] = sqrt(sum/B.rows);
        }
        

        //New temporary centroids
        for(int i=0; i<25;i++){
            c1[i] = mean1[i] - std1[i];
            c2[i] = mean1[i] + std1[i];
            c3[i] = mean2[i] - std2[i];
            c4[i] = mean2[i] + std2[i];
        }
        
        while(check){
            sum = 0;
            //Final labels
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0; dist2 = 0;
                dist3 = 0; dist4 = 0;
                
                //cout << "centers:" << c1[i] << ", " << c2[i] << ", " << c3[i] << ", " << c4[i] << endl;
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                    dist3 += pow(dataTrain.at<float>(i,j) - c3[j],2);
                    dist4 += pow(dataTrain.at<float>(i,j) - c4[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                dist3 = sqrt(dist3);
                dist4 = sqrt(dist4);
                //cout << "dist: " << dist1 << ", " << dist2 << ", " << dist3 << ", " << dist4 << endl;
                
                //Compare distances
                if(dist1<dist2 && dist1<dist3 && dist1<dist4) label[i] = 1;
                else if(dist2<dist1 && dist2<dist3 && dist2<dist4) label[i] = 2;
                else if(dist3<dist1 && dist3<dist2 && dist3<dist4) label[i] = 3;
                else label[i] = 4;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
                //cout << label[i] << ", " << tempLabel[i] << ", " << sum << endl;
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2,sum3,sum4;
                int counter1,counter2,counter3,counter4;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0; sum3 = 0; sum4 = 0;
                    counter1 = 0; counter2 = 0;
                    counter3 = 0; counter4 = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1){
                            sum1 += dataTrain.at<float>(j,i);
                            counter1++;}
                        else if(label[j]==2){
                            sum2 += dataTrain.at<float>(j,i);
                            counter2++;}
                        else if(label[j]==3){
                            sum3 += dataTrain.at<float>(j,i);
                            counter3++;}
                        else{
                            sum4 += dataTrain.at<float>(j,i);
                            counter4++;}
                    }
                    c1[i] = sum1/counter1;
                    c2[i] = sum2/counter2;
                    c3[i] = sum3/counter3;
                    c4[i] = sum4/counter4;
                    //cout << "computed:" << c1[i] << ", " << c2[i] << ", " << c3[i] << ", " << c4[i] << endl;
                }
            }
        }
    }
    
    else{//supervised method a.k.a. using visual inspection on training data
       
        //labels = {1,1,1,2,2,2,3,3,3,4,4,4};
        label[0]=1;label[1]=1;label[2]=1;
        label[3]=2;label[4]=2;label[5]=2;
        label[6]=3;label[7]=3;label[8]=3;
        label[9]=4;label[10]=4;label[11]=4;
        
        for(int i=0; i<features; i++){
            c1[i]=0;c2[i]=0;c3[i]=0;c4[i]=0;
            for(int j=0; j<objects/4; j++){
                c1[i] += dataTrain.at<float>(j,i);
            }
            for(int j=objects/4; j<2*objects/4; j++){
                c2[i] += dataTrain.at<float>(j,i);
            }
            for(int j=2*objects/4; j<3*objects/4; j++){
                c3[i] += dataTrain.at<float>(j,i);
            }
            for(int j=3*objects/4; j<objects; j++){
                c4[i] += dataTrain.at<float>(j,i);
            }
            
            //Find the centroids
            c1[i] /= (objects/4);
            c2[i] /= (objects/4);
            c3[i] /= (objects/4);
            c4[i] /= (objects/4);
        }
    }
    
    
    //Classify testing data based on the classifer obtained from the training data
    objects = dataTest.rows;
    features = dataTest.cols;
    double dist1,dist2,dist3,dist4;
    
    for(int i=0; i<objects; i++){
        dist1 = 0; dist2 = 0;
        dist3 = 0; dist4 = 0;
        
        for(int j=0; j<features; j++){
            dist1 += pow(dataTest.at<float>(i,j) - c1[j],2);
            dist2 += pow(dataTest.at<float>(i,j) - c2[j],2);
            dist3 += pow(dataTest.at<float>(i,j) - c3[j],2);
            dist4 += pow(dataTest.at<float>(i,j) - c4[j],2);
        }
        dist1 = sqrt(dist1);
        dist2 = sqrt(dist2);
        dist3 = sqrt(dist3);
        dist4 = sqrt(dist4);
       //cout << "dist:" << dist1 << ", " << dist2 << ", " << dist3 << ", " << dist4 << endl;
        
        //Compare distances
        if(dist1<dist2 && dist1<dist3 && dist1<dist4) labelTest[i] = 1;
        else if(dist2<dist1 && dist2<dist3 && dist2<dist4) labelTest[i] = 2;
        else if(dist3<dist1 && dist3<dist2 && dist3<dist4) labelTest[i] = 3;
        else labelTest[i] = 4;
        
        //cout << labelTest[i] << endl;
    }
    
}

void findLabels2(Mat dataTrain, int clusters, int *label){
    int objects = dataTrain.rows;
    int features = dataTrain.cols;
    double sum=0, mean[features],std[features];
    
    if (clusters==4){
        for(int i=0; i<features; i++){
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += dataTrain.at<float>(j,i);
            }
            mean[i] = sum/objects;
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += pow(dataTrain.at<float>(j,i) - mean[i],2);
            }
            std[i] = sqrt(sum/objects);
        }
        
        //temp centroids
        double c1[features],c2[features],c3[features],c4[features];
        for(int i=0; i<25;i++){
            c1[i] = mean[i] - std[i];
            c2[i] = mean[i] + std[i];
        }
        
        //Find temp label using euclidean distance
        double dist1, dist2, dist3, dist4, tempLabel[objects];
        bool check = true;
        
        for(int i=0;i<objects;i++){
            label[i] = 0;
        }
        
        while(check){ //Check cluster of 2
            sum = 0;
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0;dist2 = 0;
                
                //cout << "centers:" << c1[i] << ", " << c2[i] << endl;
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                //cout << "dist: " << dist1 << ", " << dist2 << endl;
                
                //Compare distances
                if(dist1<dist2) label[i] = 1;
                else    label[i] = 2;
                
                //cout << label[i] << endl;
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
                //cout << label[i] << ", " << tempLabel[i] << ", " << sum << endl;
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2;
                int counter;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0;
                    counter = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1) sum1 += dataTrain.at<float>(j,i);
                        else{
                            sum2 += dataTrain.at<float>(j,i);
                            counter++;
                        }
                    }
                    c1[i] = sum1/(objects-counter);
                    c2[i] = sum2/counter;
                    //cout << "computed:" << c1[i] << ", " << c2[i] << endl;
                }
                //cout << endl << endl;
            }
        }
        
        //New mat containing 2 clusters to be used to find 4 clusters
        Mat A,B;
        //Find new label using euclidean distance
        double mean1[features],mean2[features],std1[features],std2[features];
        check = true; //flag
        
        //Find temporary centroids for 4 clusters
        for(int i=0; i<objects;i++){
            if(tempLabel[i]==1) A.push_back(dataTrain.row(i));
            else B.push_back(dataTrain.row(i));
        }
        
        for(int i=0; i<A.cols; i++){
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += A.at<float>(j,i);
            }
            mean1[i] = sum/A.rows;
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += pow(A.at<float>(j,i) - mean1[i],2);
            }
            std1[i] = sqrt(sum/A.rows);
        }
        
        
        for(int i=0; i<B.cols; i++){
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += B.at<float>(j,i);
            }
            mean2[i] = sum/B.rows;
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += pow(B.at<float>(j,i) - mean2[i],2);
            }
            std2[i] = sqrt(sum/B.rows);
        }
        
        
        //New temporary centroids
        for(int i=0; i<25;i++){
            c1[i] = mean1[i] - std1[i];
            c2[i] = mean1[i] + std1[i];
            c3[i] = mean2[i] - std2[i];
            c4[i] = mean2[i] + std2[i];
        }
        
        while(check){
            sum = 0;
            //Final labels
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0; dist2 = 0;
                dist3 = 0; dist4 = 0;
                
                //cout << "centers:" << c1[i] << ", " << c2[i] << ", " << c3[i] << ", " << c4[i] << endl;
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                    dist3 += pow(dataTrain.at<float>(i,j) - c3[j],2);
                    dist4 += pow(dataTrain.at<float>(i,j) - c4[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                dist3 = sqrt(dist3);
                dist4 = sqrt(dist4);
                //cout << "dist: " << dist1 << ", " << dist2 << ", " << dist3 << ", " << dist4 << endl;
                
                //Compare distances
                if(dist1<dist2 && dist1<dist3 && dist1<dist4) label[i] = 1;
                else if(dist2<dist1 && dist2<dist3 && dist2<dist4) label[i] = 2;
                else if(dist3<dist1 && dist3<dist2 && dist3<dist4) label[i] = 3;
                else label[i] = 4;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
                //cout << label[i] << ", " << tempLabel[i] << ", " << sum << endl;
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2,sum3,sum4;
                int counter1,counter2,counter3,counter4;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0; sum3 = 0; sum4 = 0;
                    counter1 = 0; counter2 = 0;
                    counter3 = 0; counter4 = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1){
                            sum1 += dataTrain.at<float>(j,i);
                            counter1++;}
                        else if(label[j]==2){
                            sum2 += dataTrain.at<float>(j,i);
                            counter2++;}
                        else if(label[j]==3){
                            sum3 += dataTrain.at<float>(j,i);
                            counter3++;}
                        else{
                            sum4 += dataTrain.at<float>(j,i);
                            counter4++;}
                    }
                    c1[i] = sum1/counter1;
                    c2[i] = sum2/counter2;
                    c3[i] = sum3/counter3;
                    c4[i] = sum4/counter4;
                    //cout << "computed:" << c1[i] << ", " << c2[i] << ", " << c3[i] << ", " << c4[i] << endl;
                }
            }
        }
    }
    

    else if(clusters==6){
        for(int i=0; i<features; i++){
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += dataTrain.at<float>(j,i);
            }
            mean[i] = sum/objects;
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += pow(dataTrain.at<float>(j,i) - mean[i],2);
            }
            std[i] = sqrt(sum/objects);
        }
        
        //temp centroids
        double c1[features],c2[features],c3[features],c4[features],c5[features],c6[features];
        for(int i=0; i<25;i++){
            c1[i] = mean[i] - std[i];
            c2[i] = mean[i] + std[i];
        }
        
        //Find temp label using euclidean distance
        double dist1, dist2, dist3, dist4, dist5, dist6,tempLabel[objects];
        bool check = true;
        
        for(int i=0;i<objects;i++){
            label[i] = 0;
        }
        
        while(check){ //Check cluster of 2
            sum = 0;
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0;dist2 = 0;
                
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                
                //Compare distances
                if(dist1<dist2) label[i] = 1;
                else    label[i] = 2;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2;
                int counter;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0;
                    counter = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1) sum1 += dataTrain.at<float>(j,i);
                        else{
                            sum2 += dataTrain.at<float>(j,i);
                            counter++;
                        }
                    }
                    c1[i] = sum1/(objects-counter);
                    c2[i] = sum2/counter;
                }
            }
        }
        
        //New mat containing 2 clusters to be used to find 4 clusters
        Mat A,B;
        //Find new label using euclidean distance
        double mean1[features],mean2[features],std1[features],std2[features];
        check = true; //flag
        
        //Find temporary centroids for 4 clusters
        for(int i=0; i<objects;i++){
            if(tempLabel[i]==1) A.push_back(dataTrain.row(i));
            else B.push_back(dataTrain.row(i));
        }
        
        for(int i=0; i<A.cols; i++){
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += A.at<float>(j,i);
            }
            mean1[i] = sum/A.rows;
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += pow(A.at<float>(j,i) - mean1[i],2);
            }
            std1[i] = sqrt(sum/A.rows);
        }
        
        
        for(int i=0; i<B.cols; i++){
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += B.at<float>(j,i);
            }
            mean2[i] = sum/B.rows;
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += pow(B.at<float>(j,i) - mean2[i],2);
            }
            std2[i] = sqrt(sum/B.rows);
        }
        
        
        //New temporary centroids
        for(int i=0; i<25;i++){
            c1[i] = mean1[i] - std1[i];
            c2[i] = mean1[i] + std1[i];
            c3[i] = mean2[i] - std2[i];
            c4[i] = mean2[i] + std2[i];
            c5[i] = mean2[i];
            c6[i] = mean1[i];
        }
        
        while(check){
            sum = 0;
            //Final labels
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0; dist2 = 0; dist6 = 0;
                dist3 = 0; dist4 = 0; dist5 = 0;
                
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                    dist3 += pow(dataTrain.at<float>(i,j) - c3[j],2);
                    dist4 += pow(dataTrain.at<float>(i,j) - c4[j],2);
                    dist5 += pow(dataTrain.at<float>(i,j) - c5[j],2);
                    dist6 += pow(dataTrain.at<float>(i,j) - c6[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                dist3 = sqrt(dist3);
                dist4 = sqrt(dist4);
                dist5 = sqrt(dist5);
                dist6 = sqrt(dist6);
                
                //Compare distances
                if(dist1<dist2 && dist1<dist3 && dist1<dist4 && dist1<dist5 && dist1<dist6) label[i] = 1;
                else if(dist2<dist1 && dist2<dist3 && dist2<dist4 && dist2<dist5 && dist2<dist6) label[i] = 2;
                else if(dist3<dist1 && dist3<dist2 && dist3<dist4 && dist3<dist5 && dist3<dist6) label[i] = 3;
                else if(dist4<dist1 && dist4<dist2 && dist4<dist3 && dist4<dist5 && dist4<dist6) label[i] = 4;
                else if(dist5<dist1 && dist5<dist2 && dist5<dist3 && dist5<dist4 && dist5<dist6) label[i] = 5;
                else label[i] = 6;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2,sum3,sum4,sum5,sum6;
                int counter1,counter2,counter3,counter4,counter5,counter6;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0; sum3 = 0; sum4 = 0; sum5 = 0; sum6 = 0;
                    counter1 = 0; counter2 = 0; counter6 = 0;
                    counter3 = 0; counter4 = 0; counter5 = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1){
                            sum1 += dataTrain.at<float>(j,i);
                            counter1++;}
                        else if(label[j]==2){
                            sum2 += dataTrain.at<float>(j,i);
                            counter2++;}
                        else if(label[j]==3){
                            sum3 += dataTrain.at<float>(j,i);
                            counter3++;}
                        else if(label[j]==4){
                            sum4 += dataTrain.at<float>(j,i);
                            counter4++;}
                        else if(label[j]==5){
                            sum5 += dataTrain.at<float>(j,i);
                            counter5++;}
                        else{
                            sum6 += dataTrain.at<float>(j,i);
                            counter6++;}
                    }
                    c1[i] = sum1/counter1;
                    c2[i] = sum2/counter2;
                    c3[i] = sum3/counter3;
                    c4[i] = sum4/counter4;
                    c5[i] = sum5/counter5;
                    c6[i] = sum6/counter6;
                }
            }
        }
        
    }
        
    else if(clusters==5){
        for(int i=0; i<features; i++){
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += dataTrain.at<float>(j,i);
            }
            mean[i] = sum/objects;
            sum = 0;
            for(int j=0; j<objects; j++){
                sum += pow(dataTrain.at<float>(j,i) - mean[i],2);
            }
            std[i] = sqrt(sum/objects);
        }
        
        //temp centroids
        double c1[features],c2[features],c3[features],c4[features],c5[features];
        for(int i=0; i<25;i++){
            c1[i] = mean[i] - std[i];
            c2[i] = mean[i] + std[i];
        }
        
        //Find temp label using euclidean distance
        double dist1, dist2, dist3, dist4, dist5, tempLabel[objects];
        bool check = true;
        
        for(int i=0;i<objects;i++){
            label[i] = 0;
        }
        
        while(check){ //Check cluster of 2
            sum = 0;
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0;dist2 = 0;
                
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                
                //Compare distances
                if(dist1<dist2) label[i] = 1;
                else    label[i] = 2;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2;
                int counter;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0;
                    counter = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1) sum1 += dataTrain.at<float>(j,i);
                        else{
                            sum2 += dataTrain.at<float>(j,i);
                            counter++;
                        }
                    }
                    c1[i] = sum1/(objects-counter);
                    c2[i] = sum2/counter;
                }
            }
        }
        
        //New mat containing 2 clusters to be used to find 4 clusters
        Mat A,B;
        //Find new label using euclidean distance
        double mean1[features],mean2[features],std1[features],std2[features];
        check = true; //flag
        
        //Find temporary centroids for 4 clusters
        for(int i=0; i<objects;i++){
            if(tempLabel[i]==1) A.push_back(dataTrain.row(i));
            else B.push_back(dataTrain.row(i));
        }
        
        for(int i=0; i<A.cols; i++){
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += A.at<float>(j,i);
            }
            mean1[i] = sum/A.rows;
            sum = 0;
            for(int j=0; j<A.rows; j++){
                sum += pow(A.at<float>(j,i) - mean1[i],2);
            }
            std1[i] = sqrt(sum/A.rows);
        }
        
        
        for(int i=0; i<B.cols; i++){
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += B.at<float>(j,i);
            }
            mean2[i] = sum/B.rows;
            sum = 0;
            for(int j=0; j<B.rows; j++){
                sum += pow(B.at<float>(j,i) - mean2[i],2);
            }
            std2[i] = sqrt(sum/B.rows);
        }
        
        
        //New temporary centroids
        for(int i=0; i<25;i++){
            c1[i] = mean1[i] - std1[i];
            c2[i] = mean1[i] + std1[i];
            c3[i] = mean2[i] - std2[i];
            c4[i] = mean2[i] + std2[i];
            c5[i] = mean2[i];
        }
        
        while(check){
            sum = 0;
            //Final labels
            for(int i=0; i<objects; i++){
                tempLabel[i] = label[i];
                label[i] = 0;
                dist1 = 0; dist2 = 0;
                dist3 = 0; dist4 = 0; dist5 = 0;
                
                for(int j=0; j<features; j++){
                    dist1 += pow(dataTrain.at<float>(i,j) - c1[j],2);
                    dist2 += pow(dataTrain.at<float>(i,j) - c2[j],2);
                    dist3 += pow(dataTrain.at<float>(i,j) - c3[j],2);
                    dist4 += pow(dataTrain.at<float>(i,j) - c4[j],2);
                    dist5 += pow(dataTrain.at<float>(i,j) - c5[j],2);
                }
                dist1 = sqrt(dist1);
                dist2 = sqrt(dist2);
                dist3 = sqrt(dist3);
                dist4 = sqrt(dist4);
                dist5 = sqrt(dist5);
                
                //Compare distances
                if(dist1<dist2 && dist1<dist3 && dist1<dist4 && dist1<dist5) label[i] = 1;
                else if(dist2<dist1 && dist2<dist3 && dist2<dist4 && dist2<dist5) label[i] = 2;
                else if(dist3<dist1 && dist3<dist2 && dist3<dist4 && dist3<dist5) label[i] = 3;
                else if(dist4<dist1 && dist4<dist2 && dist4<dist3 && dist4<dist5) label[i] = 4;
                else label[i] = 5;
                
                sum += abs(label[i] - tempLabel[i]);//Check for stable state
            }
            
            if (sum==0) check = false;
            else{ //find new centroids
                double sum1,sum2,sum3,sum4,sum5;
                int counter1,counter2,counter3,counter4,counter5;
                for(int i=0; i<features; i++){
                    sum1 = 0; sum2 = 0; sum3 = 0; sum4 = 0; sum5 = 0;
                    counter1 = 0; counter2 = 0;
                    counter3 = 0; counter4 = 0; counter5 = 0;
                    for(int j=0; j<objects; j++){
                        if(label[j]==1){
                            sum1 += dataTrain.at<float>(j,i);
                            counter1++;}
                        else if(label[j]==2){
                            sum2 += dataTrain.at<float>(j,i);
                            counter2++;}
                        else if(label[j]==3){
                            sum3 += dataTrain.at<float>(j,i);
                            counter3++;}
                        else if(label[j]==4){
                            sum4 += dataTrain.at<float>(j,i);
                            counter4++;}
                        else{
                            sum5 += dataTrain.at<float>(j,i);
                            counter5++;}
                    }
                    c1[i] = sum1/counter1;
                    c2[i] = sum2/counter2;
                    c3[i] = sum3/counter3;
                    c4[i] = sum4/counter4;
                    c5[i] = sum5/counter5;
                }
            }
        }
        
    }
    
}

void findSegmentation(ImageInfo image,int clusters,int window, std::string dataType, int reduced){

    //Setting up the Laws Filters
    int laws[25][25] = {1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1,         //L5L5
        -1,-2,0,2,1,-4,-8,0,8,4,-6,-12,0,12,6,-4,-8,0,8,4,-1,-2,0,2,1,       //L5E5
        -1,0,2,0,-1,-4,0,8,0,-4,-6,0,12,0,-6,-4,0,8,0,-4,-1,0,2,0,-1,        //L5S5
        -1,2,0,-2,1,-4,8,0,-8,4,-6,12,0,-12,6,-4,8,0,-8,4,-1,2,0,-2,1,       //L5W5
        1,-4,6,-4,1,4,-16,24,-16,4,6,-24,36,-24,6,4,-16,24,-16,4,1,-4,6,-4,1,//L5R5
        -1,-4,-6,-4,-1,-2,-8,-12,-8,-2,0,0,0,0,0,2,8,12,8,2,1,4,6,4,1,       //E5L5
        1,2,0,-2,-1,2,4,0,-4,-2,0,0,0,0,0,-2,-4,0,4,2,-1,-2,0,2,1,          //E5E5
        1,0,-2,0,1,2,0,-4,0,2,0,0,0,0,0,-2,0,4,0,-2,-1,0,2,0,-1,            //E5S5
        1,-2,0,2,-1,2,-4,0,4,-2,0,0,0,0,0,-2,4,0,-4,2,-1,2,0,-2,1,          //E5W5
        -1,4,-6,4,-1,-2,8,-12,8,-2,0,0,0,0,0,2,-8,12,-8,2,1,-4,6,-4,1,       //E5R5
        -1,-4,-6,-4,-1,0,0,0,0,0,2,8,12,8,2,0,0,0,0,0,-1,-4,-6,-4,-1,        //S5L5
        1,2,0,-2,-1,0,0,0,0,0,-2,-4,0,4,2,0,0,0,0,0,1,2,0,-2,-1,            //S5E5
        1,0,-2,0,1,0,0,0,0,0,-2,0,4,0,-2,0,0,0,0,0,1,0,-2,0,1,              //S5S5
        1,-2,0,2,-1,0,0,0,0,0,-2,4,0,-4,2,0,0,0,0,0,1,-2,0,2,-1,            //S5W5
        -1,4,-6,4,-1,0,0,0,0,0,2,-8,12,-8,2,0,0,0,0,0,-1,4,-6,4,-1,          //S5R5
        -1,-4,-6,-4,-1,2,8,12,8,2,0,0,0,0,0,-2,-8,-12,-8,-2,1,4,6,4,1,       //W5L5
        1,2,0,-2,-1,-2,-4,0,4,2,0,0,0,0,0,2,4,0,-4,-2,-1,-2,0,2,1,          //W5E5
        1,0,-2,0,1,-2,0,4,0,-2,0,0,0,0,0,2,0,-4,0,2,-1,0,2,0,-1,            //W5S5
        1,-2,0,2,-1,-2,4,0,-4,2,0,0,0,0,0,2,-4,0,4,-2,-1,2,0,-2,1,          //W5W5
        -1,4,-6,4,-1,2,-8,12,-8,2,0,0,0,0,0,-2,8,-12,8,-2,1,-4,6,-4,1,       //W5R5
        1,4,6,4,1,-4,-16,-24,-16,-4,6,24,36,24,6,-4,-16,-24,-16,-4,1,4,6,4,1,//R5L5
        -1,-2,0,2,1,4,8,0,-8,-4,-6,-12,0,12,6,4,8,0,-8,-4,-1,-2,0,2,1,       //R5E5
        -1,0,2,0,-1,4,0,-8,0,4,-6,0,12,0,-6,4,0,-8,0,4,-1,0,2,0,-1,          //R5S5
        -1,2,0,-2,1,4,-8,0,8,-4,-6,12,0,-12,6,4,-8,0,8,-4,-1,2,0,-2,1,       //R5W5
        1,-4,6,-4,1,-4,16,-24,16,-4,6,-24,36,-24,6,-4,16,-24,16,-4,1,-4,6,-4,1};//R5R5
    
    //Array to store the average energies
    int lawsCounter = 0, boxCounter = 0;
    double sum = 0;
    double globalMean = 0;
    
    //Store the features
    Mat features(image.ImageSizeCols*image.ImageSizeRows,25,CV_32F);
    
    //Read file and allocate memory
    unsigned char imageD[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageD[0][0][0],IN_FOLDER);
    
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    
    //Convert to grayscale
    for(int i=0; i<image.ImageSizeRows ;i++){
        for(int j =0; j<image.ImageSizeCols ;j++){
            imageData[i][j] = 0.21*imageD[i][j][0] + 0.72*imageD[i][j][1] + 0.07*imageD[i][j][2];

        }
    }
    image.BytesPerPixel = 1;
    writeImage(image,&imageData[0][0],OUT_FOLDER);
    
    //Create expanded image to be used with a law filter window of size 5
    expandImage(image,5,OUT_FOLDER);
    //Read expanded image
    unsigned char imageExp[image.ImageSizeRows+4][image.ImageSizeCols+4];
    ImageInfo imageE(1,image.ImageSizeCols+4,image.ImageSizeRows+4,"imageExpanded.raw");
    readImage(imageE,&imageExp[0][0],IN_FOLDER);

    //Calculating the global mean
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            globalMean += imageData[i][j];
        }
    }
    globalMean /= (image.ImageSizeRows*image.ImageSizeRows);
    
    //Variable to store positive and negative values
    double data[image.ImageSizeRows+4][image.ImageSizeCols+4];
    
    //Substract global mean from the expanded image
    for(int i=0; i<image.ImageSizeRows+4; i++){
        for(int j=0; j<image.ImageSizeCols+4; j++){
            data[i][j] = imageExp[i][j] - globalMean;
            imageData[i][j] = 0;
        }
    }

    double temp[image.ImageSizeRows][image.ImageSizeCols];

    //Pass the filters one by one
    while(lawsCounter<25){

        //Find the new filtered image
        for(int i=2; i<image.ImageSizeRows+2; i++){
            for(int j=2; j<image.ImageSizeCols+2; j++){
                temp[i-2][j-2] = 0;
                boxCounter = 0;
                sum = 0;
                for(int m=-2;m<=2;m++){
                    for(int n=-2;n<=2;n++){
                        sum +=  data[i+m][j+n]*laws[lawsCounter][boxCounter];
                        boxCounter++;
                    }
                }
                temp[i-2][j-2] = sum/boxCounter;
            }
        }
        
        //Find the feature vector of every pixel
        for(int i=0; i<image.ImageSizeRows; i++){
            for(int j=0; j<image.ImageSizeCols; j++){
                sum = 0;
                boxCounter = 0;
                for(int m=-window/2;m<=window/2;m++){
                    for(int n=-window/2;n<=window/2;n++){
                        if(i>=-m && j>=-n && i<image.ImageSizeRows-m && j<image.ImageSizeCols-n){
                            sum +=  temp[i+m][j+n]*temp[i+m][j+n];
                            boxCounter++;
                        }
                    }
                }
                sum /= boxCounter;//(window*window);
                features.at<float>(i*image.ImageSizeCols+j,lawsCounter) = sum;
            }
        }
        lawsCounter++;
    }
    
    //Perform PCA if desired
    Mat newFeatures;
    if(reduced!=0){
        PCA pcaTest(features,Mat(),CV_PCA_DATA_AS_ROW, reduced);
        pcaTest.project(features,newFeatures);
    
    }
    
    //Check if data needs to be normalized
    if(dataType == "norm"){
        //Normalize the feature vector
        float initial;
        
        if(reduced==0){ //NO PCA
            for(int i=0; i<image.ImageSizeCols*image.ImageSizeRows; i++){
                initial = features.at<float>(i,0);
                
                for(int j=0; j<25;j++){
                    features.at<float>(i,j) /= initial;
                }
            }
        }
        
        else{
            for(int i=0; i<image.ImageSizeCols*image.ImageSizeRows; i++){
                initial = newFeatures.at<float>(i,0);
                
                for(int j=0; j<reduced;j++){
                    newFeatures.at<float>(i,j) /= initial;
                }
            }
        }
    }
    
    
    //Perform k-means algorithm
    int labels[image.ImageSizeCols*image.ImageSizeRows];
    if(reduced==0) findLabels2(features,clusters,labels);
    else findLabels2(newFeatures,clusters,labels);
    
    int color[] = {};
    for(int i=0; i<clusters;i++){
        color[i] = round((i*255.0)/(clusters-1));
    }
    
    unsigned char dataOut[image.ImageSizeRows][image.ImageSizeCols];
    if (reduced!=0) dataType += ("_PCA" + to_string(reduced) + "_");
    
    image.ImageName = dataType + "segmented_C" + to_string(clusters) + "_W" + to_string(window)+ ".raw";

    //Assign color according to label
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            dataOut[i][j] = color[labels[i*image.ImageSizeCols+j]-1];
        }
    }
    
    writeImage(image,&dataOut[0][0],OUT_FOLDER);
}

void cannyEdgeDetector(ImageInfo image,double T1, double T2){
    int th1 = T1*10;
    int th2 = T2*10;
    string name = "Canny_0"+ to_string(th1) + "_0" + to_string(th2) + ".raw";
    //Read file and allocate memory
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols][image.BytesPerPixel];
    readImage(image,&imageData[0][0][0],IN_FOLDER);

    //Convert to grayscale Mat format
    Mat grayscale(image.ImageSizeRows,image.ImageSizeCols,CV_64F);
    
    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            grayscale.at<double>(i,j) = 0.21*imageData[i][j][0] + 0.72*imageData[i][j][1] + 0.07*imageData[i][j][2];
        }
    }
    //Convert to unsigned integer for used in the canny function
    grayscale.convertTo(grayscale,CV_8U);

    //Set up thresholds from 0-1 range to 0-255 range
    T1 *= 255;
    T2 *= 255;
    Mat edges;
    
    //Conduct canny edge algorithm
    Canny(grayscale,edges, T1, T2);
    edges.convertTo(edges,CV_64F);

    //Pass data from Mat to unsigned char for displaying purposes
    unsigned char imageOut[image.ImageSizeRows][image.ImageSizeCols];

    for(int i=0; i<image.ImageSizeRows; i++){
        for(int j=0; j<image.ImageSizeCols; j++){
            imageOut[i][j] = 255 - edges.at<double>(i,j);
        }
    }
    
    string input = image.ImageName.substr(0,image.ImageName.length()-4);
    image.ImageName = input + name;
    image.BytesPerPixel = 1;
    writeImage(image, &imageOut[0][0], OUT_FOLDER);

}

void removeBlob(ImageInfo image,int clusters){

    //Read file and allocate memory for grayscale image
    unsigned char imageData[image.ImageSizeRows][image.ImageSizeCols];
    readImage(image,&imageData[0][0],OUT_FOLDER);

    //Find the labels in the image
    int color[] = {};
    for(int i=0; i<clusters;i++){
        color[i] = round((i*255.0)/(clusters-1));
    }
    
    unsigned char temp[image.ImageSizeRows][image.ImageSizeCols];
    int window = 9; //max size of a blob that can be removed
    int sum=0,label=0;
    
    //Separate images into binary images: label vs rest of labels
    for(int i=0; i<clusters;i++){
        for(int m=0; m<image.ImageSizeRows; m++){
            for(int n=0; n<image.ImageSizeCols; n++){
                temp[m][n] = 0;
                if (imageData[m][n]==color[i]) temp[m][n] = 255;
            }
        }
        
        //Check for blobs
        for(int m=8; m<image.ImageSizeRows-8; m++){
            for(int n=8; n<image.ImageSizeCols-8; n++){
                //Possible blob
                if (temp[m][n]==255){
                    for(int p=-window/2; p<window/2; p++){
                        for(int q=-window/2; q<window/2; q++){
                            if(temp[m+p][n+q]==255) sum++;
                        }
                    }
                    
                    //Find if its a hole
                    if(sum<window*window && sum>window*(window-3)){
                        //Find the surrounding pixel label
                        label = imageData[m][n] + window+1;
                        
                        for(int p=-window/2; p<window/2; p++){
                            for(int q=-window/2; q<window/2; q++){
                                temp[m+p][n+1] = label;
                            }
                        }
                    }
                }
                sum = 0;
                label = 0;
            }
        }
    }
}




void evaluation(ImageInfo image,string gtName,int gtNumber,std::string* output,int outNumber,std::string method){
    
    string rawName =  image.ImageName.substr(0,image.ImageName.length()-4);
    //Output data to text file
    string filename = OUT_FOLDER + rawName + method + "_Data.txt";
    //To store file
    ofstream data(filename);
    data << "\n__________"+image.ImageName +" "+ method+"__________\n\n";
    

    float meanPrecision=0, meanRecall = 0;
    
    //Check every ground truth image to each image
    for(int i=0; i<outNumber;i++){
        for(int j=0; j<gtNumber; j++){
        
            //Read images
            unsigned char GTImage[image.ImageSizeRows][image.ImageSizeCols];
            image.ImageName = gtName+to_string(j+1)+".raw";
            readImage(image, &GTImage[0][0], IN_FOLDER);
            
            unsigned char edgeImage[image.ImageSizeRows][image.ImageSizeCols];
            image.ImageName = rawName + output[i] + ".raw";
            readImage(image, &edgeImage[0][0], OUT_FOLDER);
            
            data << "\n   Edge Map: " + image.ImageName << " and GT# "<< j+1 << endl;
            
            //Compute the false positive, true positive, false negative, true negative values
            float fp=0,tp=0,fn=0,tn=0;
        
            for(int m=0; m<image.ImageSizeRows;m++){
                for(int n=0; n<image.ImageSizeCols; n++){
                    //Detected as edge but it's not
                    if(edgeImage[m][n]==0 && GTImage[m][n] != 0) fp++;
                    //Detected as edge and it is
                    else if(edgeImage[m][n]==0 && GTImage[m][n] == 0) tp++;
                    //Detected as background but it's not
                    else if(edgeImage[m][n]!=0 && GTImage[m][n] == 0) fn++;
                    //Detected as background and it is
                    else tn++;
                }
            }
            
            float Precision = tp/(fp+tp);
            float Recall = tp/(tp+fn);
            
            data << "   Precision: " << Precision*100 << ", Recall: " << Recall*100 << endl;
            
            //To find mean values
            meanPrecision += Precision;
            meanRecall += Recall;
        }
        //To find the final mean values for each edge map
        meanPrecision /= gtNumber;
        meanRecall /= gtNumber;
        
        data << "\nMean Precision: " << meanPrecision*100 << ", Mean Recall: " << meanRecall*100 << endl;
        
        //Find precision per edge map image
        float F = 2*meanPrecision*meanRecall/(meanPrecision+meanRecall);
        
        data << "F-measure: " << F*100 << endl << endl;
    }
    data.close();
}


