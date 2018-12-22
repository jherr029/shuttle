#include "../include/distanceMatrix.h"

#include <iostream>
#include <float.h>
#include <algorithm>

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

    cout << "Distance Matrix" << endl;

    for ( auto row : matrix )
    {
        for ( auto cell : row )
        {
           cell.printMiles();
           cout << "\t"; 
        }

        cout << endl;
    }

    cout << endl;
    cout << "Duration Matrix" << endl;

    for ( auto row : matrix )
    {
        for ( auto cell : row )
        {
           cell.printMinutes();
           cout << "\t"; 
        }

        cout << endl;
    }

    cout << endl;
    cout << "Route" << endl;

    for ( auto row : matrix )
    {
        for ( auto cell : row )
        {
           cell.printRoute();
           cout << "\t"; 
        }

        cout << endl;
    }

    cout << endl;
}

void DistanceMatrix::printVertices()
{
    for ( auto y : matrix )
    {

        string vertexA = y[0].getOrigin();

        for ( auto x : y )
        {
            if ( x.getMiles() == 0 )
                continue;

            cout << "(" + vertexA + ", " + x.getDestination() << ") - " 
                << x.getMiles() << endl;
        }

        cout << endl;
    }
}

// travelling salesman problem
// Prims or kruskals. Most likely Prims

float DistanceMatrix::tsp()
{
    vector<int> vertex;

    // The limit part needs to changed later on when the program becomes complex
    for ( int i = 1; i < matrix.size(); i++ )
    {
        vertex.push_back(i);
    }


    float minPath = FLT_MAX;
    int runs = 1;

    vector<vector<string> > pathHistory;
    vector<float> timeHistory;
    vector<float> minPathVec;


    do {
        float currentPathWeight = 0;
        float curTime = 0;

        int itr = 0;

        vector<string> place;
        for ( int i = 0; i < vertex.size(); i++ )
        {
            currentPathWeight += matrix[itr][vertex[i]].getMiles();
            curTime += matrix[itr][vertex[i]].getMinutes();
            itr = vertex[i];
            place.push_back(matrix[itr][vertex[i]].getOrigin());
        }

        currentPathWeight += matrix[itr][0].getMiles();
        curTime += matrix[itr][0].getMinutes();

        minPath = min(minPath, currentPathWeight);

        runs++;
        pathHistory.push_back(place);
        minPathVec.push_back(currentPathWeight);
        timeHistory.push_back(curTime);

    } while (next_permutation(vertex.begin(), vertex.end()));

    // cout << runs << endl;
    
    int correctPathIndex = 0;
    for (; correctPathIndex < minPathVec.size(); correctPathIndex++)
    {
        // cout << minPathVec[correctPathIndex] << endl;
        if (minPath == minPathVec[correctPathIndex]) 
            break;
    }


    vector<string> shortestPath = pathHistory[correctPathIndex];
    pathHistory.clear();

    shortestPath.insert(shortestPath.begin(), matrix[0][0].getOrigin());
    shortestPath.push_back(matrix[0][0].getOrigin());

    for ( auto x : shortestPath )
    {
        // cout << x << endl;
        path.push_back(x);
    }

    cout << endl;
    // cout << "Minutes: " << timeHistory[correctPathIndex] << " Distance: "; 
    duration = timeHistory[correctPathIndex];
    miles = minPath;

    return minPath;
}

// http://127.0.0.1:5000/route/v1/driving/37.915744,-121.235618;37.922831,-121.242374?step=true
float DistanceMatrix::tspDuration()
{
    vector<int> vertex;

    // The limit part needs to changed later on when the program becomes complex
    for ( int i = 1; i < matrix.size(); i++ )
    {
        vertex.push_back(i);
    }


    float minPath = FLT_MAX;
    int runs = 1;

    vector<vector<string> > pathHistory;
    vector<float> minPathVec;
    vector<float> distanceHistory;


    do {
        float currentPathWeight = 0;
        float curDist = 0;

        int itr = 0;

        vector<string> place;
        for ( int i = 0; i < vertex.size(); i++ )
        {
            currentPathWeight += matrix[itr][vertex[i]].getMinutes();
            curDist += matrix[itr][vertex[i]].getMiles();
            itr = vertex[i];
            place.push_back(matrix[itr][vertex[i]].getOrigin());
        }

        currentPathWeight += matrix[itr][0].getMinutes();
        curDist += matrix[itr][0].getMiles();

        minPath = min(minPath, currentPathWeight);

        runs++;
        pathHistory.push_back(place);
        minPathVec.push_back(currentPathWeight);
        distanceHistory.push_back(curDist);

    } while (next_permutation(vertex.begin(), vertex.end()));

    // cout << runs << endl;
    
    int correctPathIndex = 0;
    for (; correctPathIndex < minPathVec.size(); correctPathIndex++)
    {
        // cout << minPathVec[correctPathIndex] << endl;
        if (minPath == minPathVec[correctPathIndex]) 
            break;
    }


    vector<string> shortestPath = pathHistory[correctPathIndex];
    pathHistory.clear();

    shortestPath.insert(shortestPath.begin(), matrix[0][0].getOrigin());
    shortestPath.push_back(matrix[0][0].getOrigin());

    for ( auto x : shortestPath )
    {
        // cout << x << endl;
        path.push_back(x);
    }

    cout << endl;
    // cout << "Distance: " << distanceHistory[correctPathIndex] << " Minutes: ";
    duration = minPath;
    miles = distanceHistory[correctPathIndex];

    return minPath;
}

vector<string> DistanceMatrix::getPath()
{
    return path;
}

float DistanceMatrix::getMiles()
{
    return miles;
}

float DistanceMatrix::getDuration()
{
    return duration;
}