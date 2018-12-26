#include <iostream>

#include "../include/curl.h"
#include "../include/cacheCoords.h"
#include <fstream>
#include <algorithm>

// using namespace std;
vector<string> fileReadAddresses();
vector<string> getCoords(vector<string> &);
void createMatrix(vector<string> &, vector<string> &);
void writeResultsToFile(DistanceMatrix &);
void writeErrorToFile(int);

int errorAtInput = 0;

int main(int argc, char **argv)
{

    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "read") == 0 )
        {
            vector<string> addrVec = fileReadAddresses();
            vector<string> coordVec = getCoords(addrVec);
            
            if ( coordVec.size() != 0 )
            {
                createMatrix(addrVec, coordVec);
            }

            else
                writeErrorToFile(errorAtInput);

            // Curl addrObjs(addrVec);
        }

        else if ( strcmp(argv[1], "debug") == 0 )
        {
            vector<string> addrVec;
            addrVec.push_back("4114+Chadron+Ct,+Stockton,+Ca");
            addrVec.push_back("2245+11th+st,+Stockton,+Ca");
            addrVec.push_back("4600+E+fremont+st,+stockton,+ca");
            
            vector<string> coordVec;
            coordVec.push_back("-121.235697,37.916046");
            coordVec.push_back("-121.248969,37.932950");;
            coordVec.push_back("-121.236624,37.969000");

            // getCoords(addrVec);
            createMatrix(addrVec, coordVec);
        }
    }

    return 0;
}

vector<string> fileReadAddresses()
{
    ifstream addrFile("testFile.txt");

    vector<string> addrVec;

    string line;

    if (addrFile)
    {
        while  ( getline(addrFile, line) )
        {
            if (line.size() == 0)
                break;

            replace(line.begin(), line.end(), ' ', '+');
            addrVec.push_back(line);
        }
    }

    return addrVec;
}

vector<string> getCoords(vector<string> & addrVec)
{
    CacheCoords cache;

    string coordinates;

    vector<string> coordVec;
    for ( auto addr : addrVec )
    {
        errorAtInput++;
        // cout << "curling addr" << endl;

        if ( cache.checkKey(addr) )
        {
            coordinates = cache.getValue(addr);
        }

        else
        {
            Curl addrObj(addr);
            coordinates = addrObj.coordParse();

            if (coordinates == "invalid")
            {
                break;
            }

            cache.insertKeyAndValue(addr, coordinates);
        }

        coordVec.push_back(coordinates);

    }


    if (coordinates == "invalid")
    {
        coordVec.clear();
    }

    // for ( auto coord : coordVec )
    // {
    //     cout << coord << endl;
    // }

    return coordVec;
}

void createMatrix(vector<string> & addrVec, vector<string> & coordVec)
{
    Curl pls(coordVec);
    DistanceMatrix mtx = pls.matrixParse(addrVec);

    mtx.tsp();

    writeResultsToFile(mtx);
}

void writeResultsToFile(DistanceMatrix & mtx)
{
    ofstream results("results.txt");

    if (results)
    {
        vector<string> pathHistory = mtx.getPath();

        results << pathHistory.size() << endl;

        for ( auto & address : pathHistory )
        {
            // cout << address << endl;
            results << address << "\n";
        }

        results << mtx.getDuration() << "\n";
        results << mtx.getMiles() << "\n";
    }

    results.close();
}

void writeErrorToFile(int errorAtInput)
{
    ofstream resultFile("results.txt");

    resultFile << "error" << endl;
    resultFile << errorAtInput << endl;

    resultFile.close();
}
