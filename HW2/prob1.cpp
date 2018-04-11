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
    
    /////////////////////////      PART 1.A Geometrical Warping       //////////////////////////
    //Variables for cup1
    string input = "cup1.raw";
    int cols = 500;
    int rows = 500;
    int bytes = 3; //all use the same for this problem
    
    //Read Images
    ImageInfo cup1(bytes,cols,rows,input);
    //Find the output
    doAffineWarping(cup1);
    doWarping(cup1);
    
    //Variables for cup2
    input = "cup2.raw";

    //Read Images
    ImageInfo cup2(bytes,cols,rows,input);
    //Find the output
    doAffineWarping(cup2);
    doWarping(cup2);
    
    /////////////////////////       PART 1.B Puzzle Matching        ///////////////////////////
    //Variables for pieces
    input = "piece.raw";
    cols = 500;
    rows = 500;
    bytes = 3; //all use the same for this problem
    
    //Read Images
    ImageInfo pieces(bytes,cols,rows,input);
    
    //Variables for Hillary
    input = "Hillary.raw";
    cols = 512;
    rows = 512;
    
    ImageInfo hillary(bytes,cols,rows,input);
    
    input = "Trump.raw";
    ImageInfo trump(bytes,cols,rows,input);
    
    //Find the output
    solvePuzzle(pieces,hillary,trump);
    
    
    /////////////////////////   PART 1.C Homographic Transformation   //////////////////////////
    //Variables for field
    input = "field.raw";
    cols = 972;
    rows = 648;
    bytes = 3;
    
    //Set up images
    ImageInfo field(bytes,cols,rows,input);
    
    //Variables for tartan
    //input = "tartans.raw";
    input = "trojans.raw";
    cols = 350;
    rows = 197;
    
    //Set up image
    ImageInfo trojans(bytes,cols,rows,input);
    
    //Perform transformation
    homographicTran(field,trojans);
    

    return 0;
}
