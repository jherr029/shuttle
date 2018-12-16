#ifndef CURL_H_
#define CURL_H_

// #include <iostream>
#include "jsonParse.h"

// using namespace std;

class Curl
{
    public:
        Curl();
        Curl( string );

        void curlRoute_Directions();
        void printResults();

        DistanceMatrix startParse();

    private:
        string resultString;
        int resultCode;
};

#endif