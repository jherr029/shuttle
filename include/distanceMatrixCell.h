#ifndef DISTANCEMATRIXCELL_H_
#define DISTANCEMATRIXCELL_H_

#include <iostream>

using namespace std;

class DistanceMatrixCell
{
    public:
        DistanceMatrixCell();

        void setMiles( float );
        void setMinutes( float );
        void setOrigin( string );
        void setDestination( string );
        void printMiles();
        void printMinutes();
        void printRoute();

        float getMiles();
        float getMinutes();
        string getOrigin();
        string getDestination();

    private:
        float miles;
        float minutes;
        string origin;
        string destination;

};

#endif