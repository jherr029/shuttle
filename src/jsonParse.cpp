#include "../include/jsonParse.h"
#include "../include/distanceMatrixCell.h"

#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"

#include <vector>

JsonParse::JsonParse()
{
    cout << "created JsonParse" << endl;
}

void JsonParse::createDocument( string & temp )
{
    jsonDoc.Parse(temp.c_str());
}

void JsonParse::prettyPrint()
{
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);

    jsonDoc.Accept(writer);

    cout << buffer.GetString() << endl << endl;
}

DistanceMatrix JsonParse::distanceMatrixParse()
{
    string status = jsonDoc["status"].GetString();
    // cout << status << endl;

    DistanceMatrix matrix;
    if ( status == "OK")
    {
        vector<string> tempOriginAddresses;
        int tempSize = jsonDoc["origin_addresses"].Size();

        for ( int i = 0; i < tempSize; i++ )
        {
            tempOriginAddresses.push_back( jsonDoc["origin_addresses"][i].GetString() );
        }

        vector<string> tempDestinationAddresses;
        tempSize = jsonDoc["destination_addresses"].Size();
        // cout << tempSize << endl;

        for ( int i = 0; i < tempSize; i++ )
        {
            tempDestinationAddresses.push_back( jsonDoc["destination_addresses"][i].GetString() );
        }


        // vector<vector<DistanceMatrixCell> > matrix;
        Value & rows = jsonDoc["rows"];
        int rowSize = rows.Size();
        // cout << rowSize << endl;

        DistanceMatrixCell cell;
        for ( int i = 0; i < rowSize; i++ )
        {
            vector<DistanceMatrixCell> distanceCell;
            Value & innerRow = rows[i]["elements"];
            int elementsSize = innerRow.Size();

            cell.setOrigin(tempOriginAddresses[i]);

            for ( int j = 0; j < elementsSize; j++ )
            {
                if (innerRow[j]["status"] == "OK" )
                {
                    int meters = innerRow[j]["distance"]["value"].GetInt();
                    cell.setMiles(meters);
                    cell.setDestination(tempDestinationAddresses[j]);
                    distanceCell.push_back(cell);
                }
            }

            matrix.buildMatrix(distanceCell);
        }

        cout << endl;
        // matrix.printMatrix();
        // matrix.printVertices();


    }

    return matrix;

}


