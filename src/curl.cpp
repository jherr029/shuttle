#include "../include/curl.h"
// #include  "../include/jsonParse.h"

#include <curl/curl.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>

namespace 
{
    size_t WriteCallback(
        const char * in,
        size_t size,
        size_t num,
        string * out
    )

    {
        const size_t totalBytes( size * num );
        out->append( in, totalBytes );
        return totalBytes;
    }
}

Curl::Curl()
{
    cout << "Curl Initialized" << endl;
    ifstream sampleFile("../sample");

    stringstream sstr;

    if (sampleFile)
    {
        sstr << sampleFile.rdbuf();
        resultString = sstr.str();
    }
}

Curl::Curl( string addr )
{
    string distMatrix = "https://maps.googleapis.com/maps/api/geocode/json?address=" + addr + "&key=" + string(getenv("gMaps"));
    // cout << distMatrix << endl;

    CURL * curl = curl_easy_init();
    CURLcode result; // to delete later

    curl_global_init( CURL_GLOBAL_ALL );

    string readBuffer;

    curl_easy_setopt( curl, CURLOPT_URL, distMatrix.c_str() );
    curl_easy_setopt( curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt( curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);

    int httpCode(0);

    string strTemp;

    // curl_easy_setopt( curl, CURLOPT_USERPWD, userInfo.c_str() );
    // curl_easy_setopt( curl, CURLOPT_XOAUTH2_BEARER, getenv("REDDIT_KEY") );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    curl_easy_setopt( curl, CURLOPT_WRITEDATA, strTemp);

    curl_easy_perform( curl );
    curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup( curl );

    resultCode = httpCode;

    if ( httpCode == 200 )
    {
        resultString = strTemp;
        // cout << "succussful get from reddit" << endl;

    }

    else
    {
        // errorObj.setErrorInfo(true, __FILE__, __func__, __LINE__ );
        resultString = "NULL";
        // cout << "error" << endl;
        // cout << "unsuccessful get from reddit" << endl;
    }

    curl_global_cleanup();
}

Curl::Curl( vector<string> & coords )
{

    string coordString;
    for ( int i = 0; i < coords.size(); i++ )
    {
        coordString += (coords[i] + ";");
    }

    coordString.pop_back();

    cout << coordString << endl;

    string matrixUrl = "http://127.0.0.1:5000/table/v1/driving/";
    matrixUrl = matrixUrl + coordString + "?annotations=distance,duration";
    cout << matrixUrl << endl;

    // matrixUrl = "http://127.0.0.1:5000/route/v1/driving/-121.235580,37.915681;-121.240407,37.915063?steps=true";


    CURL * curl = curl_easy_init();
    CURLcode result; // to delete later

    curl_global_init( CURL_GLOBAL_ALL );

    string readBuffer;

    curl_easy_setopt( curl, CURLOPT_URL, matrixUrl.c_str() );
    curl_easy_setopt( curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt( curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);

    int httpCode(0);

    string strTemp;

    // curl_easy_setopt( curl, CURLOPT_USERPWD, userInfo.c_str() );
    // curl_easy_setopt( curl, CURLOPT_XOAUTH2_BEARER, getenv("REDDIT_KEY") );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    curl_easy_setopt( curl, CURLOPT_WRITEDATA, strTemp);

    curl_easy_perform( curl );
    curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup( curl );

    resultCode = httpCode;

    if ( httpCode == 200 )
    {
        resultString = strTemp;
        // cout << "succussful get from reddit" << endl;

    }

    else
    {
        // errorObj.setErrorInfo(true, __FILE__, __func__, __LINE__ );
        resultString = "NULL";
        // cout << "error" << endl;
        // cout << "unsuccessful get from reddit" << endl;
    }

    curl_global_cleanup();
}

void Curl::curlRoute_Directions()
{

    // string values = "Riverside,CA|Moreno+Valley,CA|Corona,CA|Fullerton,CA";
    string values = "4055+E+CALLOWAY+CT|2739+E+LOOMIS+R|212+LAZY+RIDGE+AV|1467+SNYDER+S|20075+E+KETTLEMAN+LN|672+WHIPPORWILL+ST";
    string distMatrix = "https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&origins=" + values + "&destinations=" + values + "&key=" + string(getenv("gMaps"));
    // cout << distMatrix << endl;

    CURL * curl = curl_easy_init();
    CURLcode result; // to delete later

    curl_global_init( CURL_GLOBAL_ALL );

    string readBuffer;

    curl_easy_setopt( curl, CURLOPT_URL, distMatrix.c_str() );
    curl_easy_setopt( curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt( curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt( curl, CURLOPT_FOLLOWLOCATION, 1L);

    int httpCode(0);

    string strTemp;

    // curl_easy_setopt( curl, CURLOPT_USERPWD, userInfo.c_str() );
    // curl_easy_setopt( curl, CURLOPT_XOAUTH2_BEARER, getenv("REDDIT_KEY") );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteCallback );

    curl_easy_setopt( curl, CURLOPT_WRITEDATA, strTemp);

    curl_easy_perform( curl );
    curl_easy_getinfo( curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup( curl );

    resultCode = httpCode;

    if ( httpCode == 200 )
    {
        resultString = strTemp;
        // cout << "succussful get from reddit" << endl;

    }

    else
    {
        // errorObj.setErrorInfo(true, __FILE__, __func__, __LINE__ );
        resultString = "NULL";
        // cout << "error" << endl;
        // cout << "unsuccessful get from reddit" << endl;
    }

    curl_global_cleanup();
}

DistanceMatrix Curl::matrixParse(vector<string> addrVec)
{
    JsonParse temp;
    temp.createDocument(resultString);
    return temp.distanceMatrixParse(addrVec);
    // temp.prettyPrint();
}

string Curl::coordParse()
{
    JsonParse temp;
    temp.createDocument(resultString);
    return temp.coordsParse();
}

void Curl::printResults()
{
    cout << resultCode << endl;
    cout << resultString << endl;
}