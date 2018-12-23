#include "../include/cacheCoords.h"

CacheCoords::CacheCoords()
{
    readCacheFile();

    cacheFile.open("coordCacheFile.txt", ios_base::app);
}

CacheCoords::~CacheCoords()
{
    coordCacheMap.clear();
    cacheFile.close();
}

void CacheCoords::readCacheFile()
{
    ifstream cacheFile("coordCacheFile.txt");

    if (cacheFile)
    {
        string line;
        while( getline(cacheFile, line) )
        {
            stringKeyValueParser(line);
        }
    }

    cacheFile.close();
}

void CacheCoords::stringKeyValueParser(string & str)
{
    string delimiter = "::";
    string key, value;

    // maybe use more arguments for find
    int delimiterPosition = str.find(delimiter);

    if ( delimiterPosition == std::string::npos )
    {
        cout << "could not find delimiter" << endl;
        return;
    }

    key = str.substr(0, delimiterPosition);
    value = str.substr(delimiterPosition + 2);

    // cout << "key: " << key << " Value:" << value << endl;

    coordCacheMap[key] = value;
}

bool CacheCoords::checkKey(string & key)
{
    if ( coordCacheMap.find(key) != coordCacheMap.end() )
        return true;
    
    return false;
}

void CacheCoords::insertKeyAndValue(string & key, string & value)
{
    coordCacheMap[key] = value;
    cacheFile << key << "::" << value << "\n";
}

string CacheCoords::getValue(string & key)
{
    return coordCacheMap[key];
}