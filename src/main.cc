#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stack>

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
            vector<int16_t> path = Tile::fromDegrees(DegreesPoint(lon,lat), quadtreeDepth).path();

            Node* currentNode = quadtreeRoot;

            //increase counter
            currentNode->objectCount++;

            for(auto i = 0; i < quadtreeDepth; i++)
            {
                vector<int16_t>::const_iterator firstElement = path.begin();
                vector<int16_t>::const_iterator lastElement = firstElement + (i + 1);
                vector<int16_t> nodeAddress(firstElement, lastElement);

                //if(firstElement == lastElement)
                    //nodeAddress.push_back(path[i]);

                switch(path[i])
                {
                    case 0:
                        if(currentNode->a == NULL)
                            currentNode->a = new Node(nodeAddress);

                        currentNode = currentNode->a;
                        break;
                    case 1:
                        if(currentNode->b == NULL)
                            currentNode->b = new Node(nodeAddress);

                        currentNode = currentNode->b;
                        break;
                    case 2:
                        if(currentNode->c == NULL)
                            currentNode->c = new Node(nodeAddress);

                        currentNode = currentNode->c;
                        break;
                    case 3:
                        if(currentNode->d == NULL)
                            currentNode->d = new Node(nodeAddress);

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
    Node* previousLeafNode;


    int numThreads = 8;
    int64_t numObjects = quadtree->objectCount;
    int64_t baseLine = numObjects / numThreads;
    int64_t currentSum = 0;

    vector<AddressType> splitNodes;

    stack<Node*> nodeStack;

    nodeStack.push(quadtree);

    while (!nodeStack.empty())
    {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        //if its a leaf, increment counter
        if(currentNode->a == NULL && currentNode->b == NULL && currentNode->c == NULL && currentNode->d == NULL)
        {
            currentSum += currentNode->objectCount;

            //split, store Address of Node
            if(currentSum > baseLine)
            {
                splitNodes.push_back(previousLeafNode->address);
                currentSum = 0;
            }

            previousLeafNode = currentNode;
        }

        //push childes on stack
        if (currentNode->d != NULL)
            nodeStack.push(currentNode->d);
        if (currentNode->c != NULL)
            nodeStack.push(currentNode->c);
        if (currentNode->b != NULL)
            nodeStack.push(currentNode->b);
        if (currentNode->a != NULL)
            nodeStack.push(currentNode->a);
    }


    return 0;
}
