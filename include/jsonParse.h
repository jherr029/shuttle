#ifndef JSONPARSE_H_
#define JSONPARSE_H_

// #include <iostream>
#include "./rapidjson/document.h"
#include "distanceMatrix.h"

using namespace rapidjson;
using namespace std;

class JsonParse
{
    public:
        JsonParse();

        void prettyPrint();

        void createDocument( string & );
        DistanceMatrix distanceMatrixParse();
    
    private:
        Document jsonDoc;

};

#endif