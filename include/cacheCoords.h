#ifndef CACHECOORDS_H_
#define CACHECOORDS_H_

#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

class CacheCoords
{
    public:
        CacheCoords();
        ~CacheCoords();

        bool checkKey(string &);
        void insertKeyAndValue(string &, string &);
        string getValue(string &);

    private:
        void readCacheFile();
        void appendCacheFile();
        void stringKeyValueParser(string &);
        unordered_map<string,string> coordCacheMap;
        ofstream cacheFile;
};

#endif