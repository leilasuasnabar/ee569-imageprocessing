//-----------------------------
//  EE 569 Assignment 3
//  Date: 03/20/17
//  Name: Leila Suasnabar
//  ID: 3109-9816-56
//  email: lsuasnab@usc.edu
//-----------------------------

#include <iostream>
#include <string>
#include "myFunctions.h"

using namespace std;

int main(){
    //CV version is 3.2.0
    
    /////////////////////////      PART 1.A Texture Classification        //////////////////////////
    //Variables for cup1
    string input = "Texture1.raw";
    int cols = 128;
    int rows = 128;
    int bytes = 1;
    
    //Setup Images
    ImageInfo text(bytes,cols,rows,input);
    //Find the output
    classifyTex(text,"Texture",12,6);
    
    /////////////////////////      PART 1.B Texture Segmentation        //////////////////////////
    input = "kitten.raw";
    cols = 590;//598;
    rows = 350;//448;
    bytes = 3;

    //Setup Image
    ImageInfo cat(bytes,cols,rows,input);
    
    findSegmentation(cat,4,5,"norm",0); //4 represents the # of clusters, and 15 the size of the window,
                                        //"norm" indicates normalization, and 0 indicated no PCA
    findSegmentation(cat,4,15,"norm",0);
    findSegmentation(cat,4,25,"norm",0);
    findSegmentation(cat,4,35,"norm",0);
    findSegmentation(cat,5,15,"norm",0);
    findSegmentation(cat,5,25,"norm",0);
    findSegmentation(cat,6,15,"norm",0);
    findSegmentation(cat,6,25,"norm",0);
    
    /////////////////////////      PART 1.C Advanced        //////////////////////////
    
    findSegmentation(cat,4,15,"unnorm",0);
    findSegmentation(cat,4,25,"unnorm",0);
    findSegmentation(cat,5,15,"unnorm",0);
    findSegmentation(cat,5,25,"unnorm",0);
    findSegmentation(cat,6,15,"unnorm",0);
    findSegmentation(cat,6,25,"unnorm",0);
    
    findSegmentation(cat,4,15,"unnorm",5); // 5 indicates reduced to 5 features using PCA
    findSegmentation(cat,4,25,"unnorm",5);
    findSegmentation(cat,4,25,"unnorm",1);
    findSegmentation(cat,4,25,"unnorm",3);
    findSegmentation(cat,4,25,"unnorm",7);
     
    //Clean up best output
    cat.ImageName = "unnormsegmented_C4_W25.raw";
    cat.BytesPerPixel = 1;
    removeBlob(cat,4); //4 indicated the number of clusters in the image
    

    
    return 0;
}
