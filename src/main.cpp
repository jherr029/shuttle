#include <iostream>

#include "../include/curl.h"
#include <fstream>
#include <algorithm>

// using namespace std;
vector<string> fileReadAddresses();
void getCoords(vector<string>);

int main(int argc, char **argv)
{
    // Curl sample;
    // cout << sample.coordParse() << endl;
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "read") == 0 )
        {

            vector<string> addrVec = fileReadAddresses();

            for ( auto & x : addrVec )
            {
                cout << x << endl;
            }

            getCoords(addrVec);
            // Curl addrObjs(addrVec);
        }
    }

    // Curl tempObj("hi");
    // Curl tempObj;

    // vector<string> coordStrings;
    // string strTemp;

    // ifstream coordFile("../coords.txt");

    // if (coordFile)
    // {
    //     while ( getline(coordFile, strTemp) )
    //     {
    //         coordStrings.push_back(strTemp);
    //     }
    // }

    // Curl obj(coordStrings);
    // // obj.printResults();
    // DistanceMatrix tempMatrix = obj.startParse();
    // // tempObj.curlRoute_Directions();
    // // tempObj.printResults();
    // // DistanceMatrix temp = tempObj.startParse();

    // tempMatrix.printMatrix();
    // cout << tempMatrix.tsp() << endl << endl;
    // cout << tempMatrix.tspDuration() << endl;

    return 0;
}

vector<string> fileReadAddresses()
{
    ifstream addrFile("../testFile.txt");

    vector<string> addrVec;

    string line;

    if (addrFile)
    {
        while  ( getline(addrFile, line) )
        {
            replace(line.begin(), line.end(), ' ', '+');
            addrVec.push_back(line);
        }
    }

    return addrVec;
}

void getCoords(vector<string> addrVec)
{
    vector<string> coordVec;
    for ( auto addr : addrVec )
    {
        // cout << addr << endl;
        Curl addrObj(addr);
        coordVec.push_back(addrObj.coordParse());
    }

    // for ( auto coord : coordVec )
    // {
    //     cout << coord << endl;
    // }

    Curl pls(coordVec);
    DistanceMatrix mtx = pls.matrixParse(addrVec);

    // mtx.printMatrix();
    cout << mtx.tsp();

}