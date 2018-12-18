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
        vector<string> tempDestinationAddresses;
        int tempSize = jsonDoc["origin_addresses"].Size();

        string addr;

        vector<int> validElements;

        // This is only true when the addressed are symmetric
        for ( int i = 0; i < tempSize; i++ )
        {
            addr = jsonDoc["origin_addresses"][i].GetString();
            if ( addr.size() != 0 )
            {
                // cout << addr << endl;
                tempOriginAddresses.push_back( addr );
                validElements.push_back(i);
                // tempDestinationAddresses.push_back( addr );
            }
        }

        tempSize = jsonDoc["destination_addresses"].Size();
        // cout << tempSize << endl;

        for ( int i = 0; i < tempSize; i++ )
        {
            addr = jsonDoc["destination_addresses"][i].GetString();

            if ( addr.size() != 0 )
            {
                // cout << addr << endl;
                tempDestinationAddresses.push_back( addr );
            }
        }


        // vector<vector<DistanceMatrixCell> > matrix;
        Value & rows = jsonDoc["rows"];
        int rowSize = rows.Size();
        // cout << rowSize << endl;

        // cout << tempOriginAddresses.size() << " size of dest" << endl;

        DistanceMatrixCell cell;
        for ( int i = 0; i < validElements.size(); i++ )
        {
            // cout << "i: " << i << endl;
            vector<DistanceMatrixCell> distanceCell;
            Value & innerRow = rows[validElements[i]]["elements"];
            int elementsSize = innerRow.Size();
            // cout << "element size: " << elementsSize << endl;

            cell.setOrigin(tempOriginAddresses[i]);
            int stepBack = 0;
            

            for ( int j = 0; j < elementsSize; j++ )
            {
                // cout << "j: " << j << endl;
                if (innerRow[j]["status"] == "OK" )
                {
                    int meters = innerRow[j]["distance"]["value"].GetInt();
                    cout << meters << "---" << tempDestinationAddresses[j - stepBack] << endl;
                    cell.setMiles(meters);
                    cell.setDestination(tempDestinationAddresses[j - stepBack]);
                    distanceCell.push_back(cell);
                }
                else
                {
                    // cout << "NOT_OKAY" << endl;
                    stepBack++;
                }
            }
            cout << endl;

            matrix.buildMatrix(distanceCell);
        }

        cout << endl;
        // matrix.printMatrix();
        // matrix.printVertices();


    }

    return matrix;

}


