#include <iostream>

#include "../include/curl.h"

// using namespace std;

int main(int argc, char **argv)
{
    // Curl tempObj("hi");
    Curl tempObj;

    tempObj.curlRoute_Directions();
    // tempObj.printResults();
    DistanceMatrix temp = tempObj.startParse();

    temp.printMatrix();

    return 0;
}