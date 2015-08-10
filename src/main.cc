#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>


#include "degreespoint.hh"
#include "tile.hh"

using namespace std;

int main(int argc, char** args)
{
    double lat, lon;
    ifstream txtFile(*(args + sizeof(char)));

    //read tsv file line by line
    for(string line; getline(txtFile, line); )
    {
        //extract lat and lon
        string item;
        stringstream ss(line);
        getline(ss, item, '|');
        lat = atof(item.c_str());
        getline(ss, item, '|');
        lon = atof(item.c_str());

        if(lat != 0.0 && lon != 0.0) //valid points
        {
            //convert to path
            std::cerr << lat << ", " << lon << std::endl;
            vector<int> path = Tile::fromDegrees(DegreesPoint(lon,lat),25).path();

            //print path
            for(auto i = 0; i < path.size(); i++)
                cout << path[i];

            cout << endl;
        }
    }

    //class Node, 4 mal integer zum zählen

    //switch

    return 0;
}
