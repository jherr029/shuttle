#include "../include/distanceMatrixCell.h"

#include <iostream>
#include <math.h>

using namespace std;

DistanceMatrixCell::DistanceMatrixCell()
{
    miles = 0;
}

void DistanceMatrixCell::setMiles( int meters )
{
    miles = roundf((meters / 1609.34f) * 100) / 100;
}

void DistanceMatrixCell::setOrigin( string origin )
{
    this->origin = origin;
}

void DistanceMatrixCell::setDestination( string destination )
{
    this->destination = destination;
}

void DistanceMatrixCell::printMiles()
{
    cout << miles;
}

void DistanceMatrixCell::printRoute()
{
    cout << origin << " -> " << destination;
}

float DistanceMatrixCell::getmiles()
{
    return miles;
}

string DistanceMatrixCell::getOrigin()
{
    return origin;
}

string DistanceMatrixCell::getDestination()
{
    return destination;
}