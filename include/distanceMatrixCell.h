#ifndef DISTANCEMATRIXCELL_H_
#define DISTANCEMATRIXCELL_H_

#include <iostream>

using namespace std;

class DistanceMatrixCell
{
    public:
        DistanceMatrixCell();

        void setMiles( int );
        void setOrigin( string );
        void setDestination( string );
        void printMiles();
        void printRoute();

        float getmiles();
        string getOrigin();
        string getDestination();

    private:
        float miles;
        string origin;
        string destination;

};

#endif