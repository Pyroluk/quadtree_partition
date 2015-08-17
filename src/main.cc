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
#include "partitionfunction.hh"

#define LOG

#ifdef LOG
#include "log.hh"
#endif

#define quadtreeDepth 25

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

    int16_t test = testQuadtreeLevel2.size();

    //read tsv file line by line
    for(auto i = 0; i < testQuadtreeLevel2.size(); i++)
    {
        Node* currentNode = quadtreeRoot;

        //increase counter
        currentNode->objectCount++;

        for(auto k = 0; k < 2; k++)
        {
            switch(testQuadtreeLevel2[i][k])
            {
                case 0:
                    if(currentNode->a == NULL)
                        currentNode->a = new Node(currentNode, 0);

                    currentNode = currentNode->a;
                    break;
                case 1:
                    if(currentNode->b == NULL)
                        currentNode->b = new Node(currentNode, 1);

                    currentNode = currentNode->b;
                    break;
                case 2:
                    if(currentNode->c == NULL)
                        currentNode->c = new Node(currentNode, 2);

                    currentNode = currentNode->c;
                    break;
                case 3:
                    if(currentNode->d == NULL)
                        currentNode->d = new Node(currentNode, 3);

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
                switch(path[i])
                {
                    case 0:
                        if(currentNode->a == NULL)
                            currentNode->a = new Node(currentNode, 0);

                        currentNode = currentNode->a;
                        break;
                    case 1:
                        if(currentNode->b == NULL)
                            currentNode->b = new Node(currentNode, 1);

                        currentNode = currentNode->b;
                        break;
                    case 2:
                        if(currentNode->c == NULL)
                            currentNode->c = new Node(currentNode, 2);

                        currentNode = currentNode->c;
                        break;
                    case 3:
                        if(currentNode->d == NULL)
                            currentNode->d = new Node(currentNode, 3);

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


vector<uint64_t> testDistrubution(string FileName, char separator, Node* quadtreeRoot)
{
    double lat, lon;
    ifstream txtFile(FileName);

    PartitionFunction* partitionFunction = new PartitionFunction(quadtreeRoot);

    vector<uint64_t> counts;
    for(int i = 0; i < partitionFunction->numThreads; i++)
        counts.push_back(0);

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

            auto n = path.size();
            AddressType result = 0;
            for (int i = n - 1; i >= 0; --i)
            {
                auto lbl = path[i];
                result += ((lbl & 0x3) << 2*i);
            }

            int thread_number = partitionFunction->getThreadIdForAddress(result, quadtreeDepth);
            ++counts[thread_number];
        }
    }

    return counts;
}

int main(int argc, char** args)
{
    Node* quadtreeRoot = generateCountQuadtree(*(args + sizeof(char)), '|'); //generateTestQuadtree();// generateCountQuadtree(*(args + sizeof(char)), '|');

    vector<uint64_t> counts = testDistrubution(*(args + sizeof(char)), '|', quadtreeRoot);

    return 0;
}
