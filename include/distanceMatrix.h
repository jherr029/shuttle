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
        float tsp();
        float tspDuration();

        vector<string> getPath();
        float getMiles();
        float getDuration();
        

    private:
        vector<vector<DistanceMatrixCell> > matrix;
        vector<string> path;
        float miles;
        float duration;

};

#endif