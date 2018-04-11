//-----------------------------
//  EE 569 Assignment 2
//  Date: 02/14/17
//  Name: Leila Suasnabar
//-----------------------------


#include <stdio.h>
#include <iostream>
#include <math.h>
#include "myFunctions.h"

using namespace std;

int main(){
    
    /////////////////////////      PART 3.A Shrinking       //////////////////////////
    //Variables for squares
    string input = "squares.raw";
    int cols = 480;
    int rows = 480;
    int bytes = 1; //all use the same for this problem
    
    //Read Images
    ImageInfo square(bytes,cols,rows,input);
    //Find the output
    morphological(square,"Shrinking",OUT_FOLDER);
    
    /////////////////////////      PART 3.B/C Thinning and Skeletonizing       //////////////////////////
    input = "letterE.raw";
    
    //Read Images
    ImageInfo letterE(bytes,cols,rows,input);
    morphological(letterE,"Thinning",OUT_FOLDER);
    morphological(letterE,"Skeletonizing",OUT_FOLDER);
    
    /////////////////////////      PART 3.D Counting Game       //////////////////////////
    input = "board.raw";
    
    //Read Images
    ImageInfo board(bytes,cols,rows,input);

    //Find number of holes and its positions
    int posHoles[20],holes;
    holes = findHoles(board,posHoles);
    
    //Use the positions as internal points to remove holes
    fillHoles(board,posHoles,holes);
    board.ImageName = "boardNoHoles.raw";
    morphological(board,"Shrinking",OUT_FOLDER);
    
    //Check number of white objects
    board.ImageName = "boardNoHoles_Shrinking.raw";
    int objects,posObjects[20];
    objects = countLonelyPixels(board,posObjects,OUT_FOLDER);
    
    board.ImageName = "boardNoHoles.raw";
    checkCircularity(board,posObjects,objects,OUT_FOLDER,OUT_FOLDER,holes);

    //Remove unneccesary images
    remove("Inputs/boardNoHoles.raw");
    
    return 0;
}
