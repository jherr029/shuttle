#include "../include/distanceMatrixCell.h"

#include <iostream>
#include <math.h>

using namespace std;

DistanceMatrixCell::DistanceMatrixCell()
{
    miles = 0;
}

void DistanceMatrixCell::setMiles( float meters )
{
    miles = roundf((meters / 1609.34f) * 100) / 100;
}

void DistanceMatrixCell::setMinutes( float seconds )
{
    minutes = roundf((seconds / 60) * 100) / 100;
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

void DistanceMatrixCell::printMinutes()
{
    cout << minutes;
}

void DistanceMatrixCell::printRoute()
{
    cout << origin << " -> " << destination;
}

float DistanceMatrixCell::getMiles()
{
    return miles;
}

float DistanceMatrixCell::getMinutes()
{
    return minutes;
}

string DistanceMatrixCell::getOrigin()
{
    return origin;
}

string DistanceMatrixCell::getDestination()
{
    return destination;
}