#ifndef DISTANCEMATRIX_H_
#define DISTANCEMATRIX_H_

#include "distanceMatrixCell.h"
#include <vector>

using namespace std;

class DistanceMatrix
{
    public:
        DistanceMatrix();

        void buildMatrix( vector<DistanceMatrixCell> );
        void printMatrix();

        void printVertices();

    private:
        vector<vector<DistanceMatrixCell> > matrix;

};

#endif