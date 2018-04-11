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
    
    /////////////////////////      PART 2.A Dithering Matrix       //////////////////////////
    //Variables for man
    string input = "man.raw";
    int cols = 512;
    int rows = 512;
    int bytes = 1; //all use the same for this problem
    
    //Read Images
    ImageInfo man(bytes,cols,rows,input);
    int n[3] = {2,8,4};//size of I matrix
    //Find the output
    dithering(man,n[0]);
    dithering(man,n[1]);
    dithering(man,n[2]);
    dithering(man,0);
    
    //A4 + I4
    input = "man_ditheredA.raw";
    man.ImageName = input;
    dithering(man,4);
    
    //I4+ D4
    input = "man_dithered4.raw";
    man.ImageName = input;
    dithering(man,0);
    
    //Dithering using 4 gray-levels
    input = "man.raw";
    man.ImageName = input;
    dithering4(man,4);
    dithering4(man,0);
    
    
    /////////////////////////      PART 2.B Error Diffusion       //////////////////////////
    
    errorDifussion(man,"Floyd-Steinberg");
    errorDifussion(man,"JJN");
    errorDifussion(man,"Stucki");
    errorDifussion(man,"Other");
    
    
    //Remove unneccesary images
    remove("Inputs/imageExpanded.raw");
    remove("Inputs/man_dithered4_ditheredA.raw");
    remove("Inputs/man_dithered4.raw");
    remove("Inputs/man_ditheredA_dithered4.raw");
    remove("Inputs/man_ditheredA.raw");
    
    return 0;
}
