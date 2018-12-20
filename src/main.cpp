#include <iostream>

#include "../include/curl.h"
#include <fstream>

// using namespace std;

int main(int argc, char **argv)
{
    // Curl tempObj("hi");
    // Curl tempObj;

    vector<string> coordStrings;
    string strTemp;

    ifstream coordFile("../coords.txt");

    if (coordFile)
    {
        while ( getline(coordFile, strTemp) )
        {
            coordStrings.push_back(strTemp);
        }
    }

    Curl obj(coordStrings);
    // obj.printResults();
    DistanceMatrix tempMatrix = obj.startParse();
    // tempObj.curlRoute_Directions();
    // tempObj.printResults();
    // DistanceMatrix temp = tempObj.startParse();

    tempMatrix.printMatrix();
    cout << tempMatrix.tsp() << endl;

    return 0;
}