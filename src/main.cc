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

#define LOG

#ifdef LOG
#include "log.hh"
#endif

#define quadtreeDepth 2

using namespace std;

Node* generateTestQuadtree()
{
    Node* quadtreeRoot = new Node();

    vector<vector<int16_t>> testQuadtreeLevel2;

    //add points
    vector<int16_t> point;

    //0,0
    point.push_back(0);
    point.push_back(0);
    testQuadtreeLevel2.push_back(point);
    point.clear();

    for(auto i = 0; i < 2; i++)
    {
        //0,1
        point.push_back(0);
        point.push_back(1);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //0,2
    point.push_back(0);
    point.push_back(2);
    testQuadtreeLevel2.push_back(point);
    point.clear();

    //0,3
    for(auto i = 0; i < 4; i++)
    {
        point.push_back(0);
        point.push_back(3);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //1,0
    for(auto i = 0; i < 8; i++)
    {
        point.push_back(1);
        point.push_back(0);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //1,1
    for(auto i = 0; i < 9; i++)
    {
        point.push_back(1);
        point.push_back(1);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //1,2
    for(auto i = 0; i < 3; i++)
    {
        point.push_back(1);
        point.push_back(2);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //1,3
    for(auto i = 0; i < 2; i++)
    {
        point.push_back(1);
        point.push_back(3);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //2,0
    point.push_back(2);
    point.push_back(0);
    testQuadtreeLevel2.push_back(point);
    point.clear();

    //2,1
    for(auto i = 0; i < 2; i++)
    {
        point.push_back(2);
        point.push_back(1);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //2,2
    for(auto i = 0; i < 3; i++)
    {
        point.push_back(2);
        point.push_back(2);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //2,3
    for(auto i = 0; i < 4; i++)
    {
        point.push_back(2);
        point.push_back(3);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //3,0
    for(auto i = 0; i < 5; i++)
    {
        point.push_back(3);
        point.push_back(0);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //3,1
    for(auto i = 0; i < 6; i++)
    {
        point.push_back(3);
        point.push_back(1);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //3,2
    point.push_back(3);
    point.push_back(2);
    testQuadtreeLevel2.push_back(point);
    point.clear();

    //3,3
    for(auto i = 0; i < 2; i++)
    {
        point.push_back(3);
        point.push_back(3);
        testQuadtreeLevel2.push_back(point);
        point.clear();
    }

    //read tsv file line by line
    for(auto i = 0; testQuadtreeLevel2.size(); i++)
    {
        //convert to path
        //std::cerr << lat << ", " << lon << std::endl;
        vector<int16_t> path = testQuadtreeLevel2[i];

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

    return quadtreeRoot;
}

Node* generateCountQuadtree(string FileName, char separator)
{
    double lat, lon;
    Node* quadtreeRoot = new Node();
    ifstream txtFile(FileName);

    #ifdef LOG
    logging::getLog().newNode((logging::NodeID)quadtreeRoot, 0, 0);
    #endif

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
                        {
                            currentNode->a = new Node(nodeAddress);

                            //#ifdef LOG
                            //logging::getLog().newNode((logging::NodeID)currentNode->a, 0, 0);
                            //#endif
                        }

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
    Node* quadtree = generateTestQuadtree();// generateCountQuadtree(*(args + sizeof(char)), '|');
    Node* lastLeave;

    int numThreads = 3;
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
                splitNodes.push_back(currentNode->address);
                currentSum = 0;
            }

            lastLeave = currentNode;
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
