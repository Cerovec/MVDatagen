/*
 * matlabLink.cpp
 *
 *  Created on: Nov 28, 2012
 *      Author: boris
 */

#ifdef MATLAB

#include "mex.h"
#include <stdio.h>
#include <stdlib.h>
#include "Dataset.h"
#include "Utils/IO.h"
#include "Marker/Marker.h"
#include "Generator/NoiseGenerator.h"
#include "Generator/BlurGenerator.h"
#include "Generator/PerspectiveGenerator.h"
#include "Generator/CopyGenerator.h"
#include "Generator/FlipGenerator.h"
#include "Gpu/GpuGenerator.hpp"
#include "Matlab.h"

/*
#include <vector>
#include <string>
#include <sstream>
using namespace std;
*/
 
void mexFunction(int nlhs,  mxArray *plhs[], int nrhs, const mxArray *prhs[])
{   
    if(nrhs!=1) 
      mexErrMsgIdAndTxt( "MATLAB:MVDatagen:invalidNumInputs",
              "One input required.");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt( "MATLAB:MVDatagen:maxlhs",
              "Too many output arguments.");
    
    if ( mxIsChar(prhs[0]) != 1)
      mexErrMsgIdAndTxt( "MATLAB:MVDatagen:inputNotString",
              "Input must be a string.");
    
    if (mxGetM(prhs[0])!=1)
      mexErrMsgIdAndTxt( "MATLAB:MVDatagen:inputNotVector",
              "Input must be a row vector.");
   
    // get c string
    char* arguments;
    arguments = mxArrayToString(prhs[0]);
    mexPrintf("arguments: %s\n", arguments);
    /*
    
    string s(arguments);
    istringstream iss(s);
    vector<string> tokens;
    tokens.push_back("MVDatagen");

    while(iss)
    {
        string sub;
        iss >> sub;
        tokens.push_back(sub);
    }
    
    int argc = tokens.size() - 1;
    char** argv;
    argv = new char* [argc];
    
    char* buf;
    for (int i = 0 ; i < argc ; i++){
        //buf = new char[tokens.at(i).size()];
        buf = (char *)mxCalloc(tokens.at(i).size(), sizeof(char));
        strcpy(buf, tokens.at(i).c_str());
        *(argv + i) = buf;
        mexPrintf("argument %d is %s\n", i, *(argv + i));
    }

    int exitStatus;
    exitStatus = main(argc, argv);
    mexPrintf("ExitStatus: %d", exitStatus);
    
    for (int i = 0 ; i < argc ; i++){
         mxFree(*(argv + i));       
    }
    delete [] argv;
     */
    
    // "/home/boris/TestImages/Barcode"
	mv::Marker marker(arguments);
	marker.markDataset();
    mxFree(arguments);
	return;
}

#endif
