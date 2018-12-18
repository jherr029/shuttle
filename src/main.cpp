#include <iostream>

#include "../include/curl.h"

// using namespace std;

int main(int argc, char **argv)
{
    Curl tempObj("hi");
    // Curl tempObj;

    // tempObj.curlRoute_Directions();
    // tempObj.printResults();
    DistanceMatrix temp = tempObj.startParse();

    temp.printMatrix();
    cout << endl;
    cout << temp.tsp() << endl;

    return 0;
}