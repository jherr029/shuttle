#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"
#include <iomanip>

#include <gtest/gtest.h>

using namespace std;
using namespace rapidjson;

namespace {


    TEST(JsonParse, doubleCorrectness)
    {
        ifstream jsonFile("../jsonFile");
        stringstream sstr;
        string resultString;
        
        if ( jsonFile.is_open() )
        {
            sstr << jsonFile.rdbuf();
            resultString = sstr.str();
        }

        else
        {
            cout << "can not open file " << endl;
        }

        Document docObj;
        docObj.Parse(resultString.c_str());

        // cout << docObj["value"].GetFloat() << endl;
        double parsedValue = docObj["value"].GetDouble();

        double temp  = 12.13456789;
        cout << setprecision(10) << parsedValue << endl;

        ASSERT_EQ(parsedValue, 12.13456789);


    }
}