#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "degreespoint.hh"
#include "tile.hh"
#include "node.hh"

#define quadtreeDepth 25

using namespace std;

Node* generateCountQuadtree(string FileName, char separator)
{
    double lat, lon;
    Node* quadtreeRoot = new Node();
    ifstream txtFile(FileName);

    //read tsv file line by line
    for(string line; getline(txtFile, line); )
    {
        //extract lat and lon
        string item;
        stringstream ss(line);
        getline(ss, item, separator);
        lat = atof(item.c_str());
        getline(ss, item, separator);
        lon = atof(item.c_str());

        if(lat != 0.0 && lon != 0.0) //valid points
        {
            //convert to path
            //std::cerr << lat << ", " << lon << std::endl;
            vector<int> path = Tile::fromDegrees(DegreesPoint(lon,lat), quadtreeDepth).path();

            Node* currentNode = quadtreeRoot;

            //increase counter
            currentNode->objectCount++;

            for(auto i = 0; i < quadtreeDepth; i++)
            {
                switch(path[i])
                {
                    case 0:
                        if(currentNode->a == NULL)
                            currentNode->a = new Node();

                        currentNode = currentNode->a;
                        break;
                    case 1:
                        if(currentNode->b == NULL)
                            currentNode->b = new Node();

                        currentNode = currentNode->b;
                        break;
                    case 2:
                        if(currentNode->c == NULL)
                            currentNode->c = new Node();

                        currentNode = currentNode->c;
                        break;
                    case 3:
                        if(currentNode->d == NULL)
                            currentNode->d = new Node();

                        currentNode = currentNode->d;
                        break;
                }

                //increase counter
                currentNode->objectCount++;
            }
        }
    }

    return quadtreeRoot;
}

int main(int argc, char** args)
{
    Node* quadtree = generateCountQuadtree(*(args + sizeof(char)), '|');

    //traverse quadtree

    //partition quadtree

    return 0;
}
