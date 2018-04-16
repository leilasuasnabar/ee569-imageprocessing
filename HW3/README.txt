# EE569 Homework Assignment #3
# Date:     03/26/17
# Name:     Leila Suasnabar
# ID:       3109-9816-56
# Email:    lsuasnab@usc.edu
#
# Compiled on OS X El Capitan Version 10.11.6 with C++11 and openCV 3.2.0
#	and MATLAB 2015b
#
# Running project:
# Put file in respective software where it can be executed
#
###IMPORTANT##:
#		THIS FOLDER CONTAINS FILE THAT MUST BE RAN FIRST IN C++ AND
#		THEN MOVE THE OUTPUT RAW IMAGES TO THE FOLDER WHERE THE MATLAB
#		FOLDER IS BEING RAN INTO.
#
#
#		FOR C++: Create folders called “Inputs” and “Outputs” in the same 
#		folder where 
#		this code is being run. Put all the images required for the
#		problems inside “Inputs”.
#
# 		Prob1.cpp contains problem 1 - C++
# 		Prob2a.cpp contains problem 2a - C++
#		myFunctions.cpp contains all the functions used on this part
#
#		Prob2b.m - Matlab file
#		Prob2c.m - Matlab file
#		Prob3.m - Matlab file
#		Functions: classify.m, rawtoData.m, SEDetection.m, SVM.m
#		
#
#
#NOTE C++: OpenCV 3.x must be installed in the program where the files are executed
#
#NOTE Matlab: The following toolboxes must have been compiled on MATLAB
#		prior to running the files.
#
#		Structured Edge Detection Toolbox      Version 3.01
# 		Code written by Piotr Dollar, 2014.
#		https://github.com/pdollar/edges
#
#		VLFeat open source library: http://www.vlfeat.org
#
#		Bag of Words functions: 
#		https://www.mathworks.com/matlabcentral/fileexchange/43631-compute-
#		bag-of-visual-word-representation-for-an-image
#		—> See report for a minor modification on computeBoV.m
#
#		Yael Library: https://gforge.inria.fr/projects/yael/
#		
#		Finally, make sure the mat file 393035.mat and 201080.mat (from the
#		Berkeley - BSDS500) are in the same folder.
#		https://www2.eecs.berkeley.edu/Research/Projects/CS/vision/grouping/
#		resources.html
#
#


