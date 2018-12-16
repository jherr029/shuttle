#include "../include/distanceMatrix.h"

#include <iostream>

DistanceMatrix::DistanceMatrix()
{
    cout << "DistanceMatrix" << endl;
}

void DistanceMatrix::buildMatrix( vector<DistanceMatrixCell> row)
{
    matrix.push_back(row);
}

void DistanceMatrix::printMatrix()
{
    for ( auto row : matrix )
    {
        for ( auto cell : row )
        {
           cell.printMiles();
           cout << "\t"; 
        }

        cout << endl;
    }

}

void DistanceMatrix::printVertices()
{
    for ( auto y : matrix )
    {

        string vertexA = y[0].getOrigin();

        for ( auto x : y )
        {
            if ( x.getmiles() == 0 )
                continue;

            cout << "(" + vertexA + ", " + x.getDestination() << ") - " 
                << x.getmiles() << endl;
        }

        cout << endl;
    }
}