#ifndef CURL_H_
#define CURL_H_

// #include <iostream>
#include "jsonParse.h"
#include <vector>

// using namespace std;

class Curl
{
    public:
        Curl();
        Curl( string );
        Curl(vector<string> &);

        void curlRoute_Directions();
        void printResults();

        DistanceMatrix matrixParse(vector<string>);
        string coordParse();

        int getCode();

    private:
        string resultString;
        int resultCode;
};

#endif