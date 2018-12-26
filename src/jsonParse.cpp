#include "../include/jsonParse.h"
#include "../include/distanceMatrixCell.h"

#include "../include/rapidjson/stringbuffer.h"
#include "../include/rapidjson/prettywriter.h"

#include <vector>

JsonParse::JsonParse()
{
    // cout << "created JsonParse" << endl;
    ;
}

void JsonParse::createDocument( string & temp )
{
    if ( temp == "NULL" )
        temp = "{ \"status\": bad}";

    jsonDoc.Parse(temp.c_str());
}

void JsonParse::prettyPrint()
{
    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);

    jsonDoc.Accept(writer);

    cout << buffer.GetString() << endl << endl;
}

DistanceMatrix JsonParse::distanceMatrixParse(vector<string> addrVec)
{
    string status = jsonDoc["code"].GetString();
    // cout << status << endl;

    DistanceMatrix matrix;
    if ( status == "Ok")
    {
        vector<string> tempOriginAddresses;
        vector<string> tempDestinationAddresses;
        int tempSize = jsonDoc["sources"].Size();

        string addr;

        vector<int> validElements;

        // This is only true when the addressed are symmetric
        for ( int i = 0; i < tempSize; i++ )
        {
            addr = jsonDoc["sources"][i]["name"].GetString();
            if ( addr.size() == 0 )
                addr = "NO NAME";

            tempOriginAddresses.push_back( addr );
            validElements.push_back(i);

            addr = jsonDoc["destinations"][i]["name"].GetString();

            if ( addr.size() == 0 )
                addr = "NO NAME";

            tempDestinationAddresses.push_back( addr );
        }

        Value & distanceRow = jsonDoc["distances"];
        Value & durationRow = jsonDoc["durations"];
        int rowSize = distanceRow.Size();
        // cout << rowSize << endl;

        // cout << tempOriginAddresses.size() << " size of dest" << endl;

        DistanceMatrixCell cell;
        for ( int i = 0; i < validElements.size(); i++ )
        {
            // cout << "i: " << i << endl;
            vector<DistanceMatrixCell> distanceCell;
            // cout << "Distance: " << rows[0][1].GetFloat() << endl;
            Value & innerDistanceRow = distanceRow[validElements[i]];
            Value & innerDurationRow = durationRow[validElements[i]];
            int elementsSize = innerDistanceRow.Size();
            // cout << "element size: " << elementsSize << endl;

            cell.setOrigin(addrVec[i]);
            int stepBack = 0;

            for ( int j = 0; j < elementsSize; j++ )
            {
                float meters = innerDistanceRow[j].GetFloat();
                float seconds = innerDurationRow[j].GetFloat();
                cell.setMiles(meters);
                cell.setMinutes(seconds);
                cell.setDestination(addrVec[j]);
                distanceCell.push_back(cell);

                // cout << meters << "---" << tempDestinationAddresses[j - stepBack] << endl;
            }
            // cout << endl;

            matrix.buildMatrix(distanceCell);
        }

        // cout << endl;
    }

    return matrix;
}

string JsonParse::coordsParse()
{
    if ( jsonDoc["status"] == "OK" )
    {
        // Value & coords = jsonDoc["results"][0]["formatted_address"];
        Value & coords = jsonDoc["results"][0]["geometry"]["location"];
        // cout << "hi" << endl;

        string lat = to_string(coords["lat"].GetDouble());
        string lng = to_string(coords["lng"].GetDouble());

        return lng + "," + lat;
    }

    return "invalid";
}
