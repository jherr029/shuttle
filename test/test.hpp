#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/curl.h"

#include <gtest/gtest.h>

using namespace std;
using namespace rapidjson;

namespace {


    TEST(Curl, address)
    {
        Curl address("4114+chadron+ct,+stockton,+ca");

        ASSERT_EQ(200, address.getCode());
        ASSERT_NE(0, address.getResult().size());

    }

    TEST(Curl, coordinates)
    {
        vector<string> coordVec;
        coordVec.push_back("-121.235697,37.916046");
        coordVec.push_back("-121.248969,37.932950");;
        coordVec.push_back("-121.236624,37.969000");

        Curl coordinates(coordVec);

        ASSERT_EQ(200, coordinates.getCode());
    }
}
