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

//using namespace cv;
using namespace std;

int main(){
    //CV version is 3.2.0
    
    /////////////////////////      PART 2.A Canny Edge Detector        //////////////////////////
    //Variables for cup1
    string input = "Castle.raw";
    int cols = 481;
    int rows = 321;
    int bytes = 3;
    
    //Setup Images
    ImageInfo castle(bytes,cols,rows,input);
    //Find the output
    
    cannyEdgeDetector(castle,0.2,0.5);
    cannyEdgeDetector(castle,0.2,0.7);
    cannyEdgeDetector(castle,0.3,0.4);
    cannyEdgeDetector(castle,0.3,0.8);
    cannyEdgeDetector(castle,0.4,0.6);
    cannyEdgeDetector(castle,0.1,0.9);
    
    input = "Boat.raw";
    //Setup Images
    ImageInfo boat(bytes,cols,rows,input);
    
    cannyEdgeDetector(boat,0.2,0.5);
    cannyEdgeDetector(boat,0.2,0.7);
    cannyEdgeDetector(boat,0.3,0.4);
    cannyEdgeDetector(boat,0.3,0.8);
    cannyEdgeDetector(boat,0.4,0.6);
    cannyEdgeDetector(boat,0.1,0.9);
    
    
    /////////////////////////      PART 2.C Evaluation - NOT INCLUDED IN THE REPORT       //////////////////////////
    input = "Castle.raw";
    string namesGT = "Castle_gt";
    string namesSE[6] = {"SE_002","SE_005","SE_010","SE_015","SE_020","SE_025"};
    string namesCanny[6] = {"Canny_02_05","Canny_02_07","Canny_03_04","Canny_03_08","Canny_04_06","Canny_01_09"};
    
    //Setup Image
    ImageInfo eval(1,cols,rows,input);
    
    evaluation(eval,namesGT,6,namesCanny,6,"Canny");
    evaluation(eval,namesGT,6,namesSE,6,"SE");
    
    eval.ImageName = "Boat.raw";
    evaluation(eval,namesGT,6,namesCanny,6,"Canny");
    evaluation(eval,namesGT,6,namesSE,6,"SE");
    
    return 0;
}















