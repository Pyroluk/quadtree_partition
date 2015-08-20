#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <stack>
#include <random>
#include <map>

#include <tclap/CmdLine.h>

#include "degreespoint.hh"
#include "tile.hh"
#include "node.hh"
#include "partitionfunction.hh"

#define LOG

#ifdef LOG
#include "log.hh"
#endif

#define quadtreeDepth 25

//-----------------------------------------------------------------
// Options
//-----------------------------------------------------------------

struct Options {

    Options(const std::vector<std::string>& args);

    TCLAP::CmdLine cmd_line { "qtpart", ' ', "0.01" };

    // -s or --schema
    TCLAP::ValueArg<std::string> input {
        "i",              // flag
        "input",         // name
        ".psv lat|lon", // description
        true,            // required
        "",               // value
        "psv_filename" // type description
    };

    // -l or -level
    TCLAP::ValueArg<int> training_size {
        "t",              // flag
        "training-size",         // name
        "training size", // description
        false,            // required
        1000,               // value
        "number" // type description
    };

    // -d or -data
    TCLAP::ValueArg<int> num_parts {
        "n",              // flag
        "num-parts",         // name
        "number of parts", // description
        true,            // required
        10,               // value
        "number"   // type description
    };

};


Options::Options(const std::vector<std::string>& args)
{
    auto args_copy = args;
    cmd_line.add(input); // add command option
    cmd_line.add(training_size);
    cmd_line.add(num_parts);
    cmd_line.parse(args_copy);
}



using namespace std;

//vector<vector<int16_t>> getQuattreeTestPoints()
//{
//    vector<vector<int16_t>> testQuadtreeLevel2;

//    //add points
//    vector<int16_t> point;

//    //0,0
//    point.push_back(0);
//    point.push_back(0);
//    testQuadtreeLevel2.push_back(point);
//    point.clear();

//    for(auto i = 0; i < 2; i++)
//    {
//        //0,1
//        point.push_back(0);
//        point.push_back(1);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //0,2
//    point.push_back(0);
//    point.push_back(2);
//    testQuadtreeLevel2.push_back(point);
//    point.clear();

//    //0,3
//    for(auto i = 0; i < 4; i++)
//    {
//        point.push_back(0);
//        point.push_back(3);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //1,0
//    for(auto i = 0; i < 8; i++)
//    {
//        point.push_back(1);
//        point.push_back(0);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //1,1
//    for(auto i = 0; i < 9; i++)
//    {
//        point.push_back(1);
//        point.push_back(1);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //1,2
//    for(auto i = 0; i < 3; i++)
//    {
//        point.push_back(1);
//        point.push_back(2);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //1,3
//    for(auto i = 0; i < 2; i++)
//    {
//        point.push_back(1);
//        point.push_back(3);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //2,0
//    point.push_back(2);
//    point.push_back(0);
//    testQuadtreeLevel2.push_back(point);
//    point.clear();

//    //2,1
//    for(auto i = 0; i < 2; i++)
//    {
//        point.push_back(2);
//        point.push_back(1);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //2,2
//    for(auto i = 0; i < 3; i++)
//    {
//        point.push_back(2);
//        point.push_back(2);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //2,3
//    for(auto i = 0; i < 4; i++)
//    {
//        point.push_back(2);
//        point.push_back(3);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //3,0
//    for(auto i = 0; i < 5; i++)
//    {
//        point.push_back(3);
//        point.push_back(0);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //3,1
//    for(auto i = 0; i < 6; i++)
//    {
//        point.push_back(3);
//        point.push_back(1);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    //3,2
//    point.push_back(3);
//    point.push_back(2);
//    testQuadtreeLevel2.push_back(point);
//    point.clear();

//    //3,3
//    for(auto i = 0; i < 2; i++)
//    {
//        point.push_back(3);
//        point.push_back(3);
//        testQuadtreeLevel2.push_back(point);
//        point.clear();
//    }

//    return testQuadtreeLevel2;
//}

//Node* generateTestQuadtree()
//{
//    Node* quadtreeRoot = new Node();

//    vector<vector<int16_t>> testQuadtreeLevel2 = getQuattreeTestPoints();

//    //read tsv file line by line
//    for(auto i = 0; i < testQuadtreeLevel2.size(); i++)
//    {
//        Node* currentNode = quadtreeRoot;

//        //increase counter
//        currentNode->objectCount++;

//        for(auto k = 0; k < 2; k++)
//        {
//            switch(testQuadtreeLevel2[i][k])
//            {
//                case 0:
//                    if(currentNode->a == NULL)
//                        currentNode->a = new Node(currentNode, 0);

//                    currentNode = currentNode->a;
//                    break;
//                case 1:
//                    if(currentNode->b == NULL)
//                        currentNode->b = new Node(currentNode, 1);

//                    currentNode = currentNode->b;
//                    break;
//                case 2:
//                    if(currentNode->c == NULL)
//                        currentNode->c = new Node(currentNode, 2);

//                    currentNode = currentNode->c;
//                    break;
//                case 3:
//                    if(currentNode->d == NULL)
//                        currentNode->d = new Node(currentNode, 3);

//                    currentNode = currentNode->d;
//                    break;
//            }

//            //increase counter
//            currentNode->objectCount++;
//        }
//    }

//    return quadtreeRoot;
//}

//Node* generateCountQuadtree(string FileName, char separator)
//{
//    double lat, lon;
//    Node* quadtreeRoot = new Node();
//    ifstream txtFile(FileName);

//    //read tsv file line by line
//    for(string line; getline(txtFile, line); )
//    {
//        //extract lat and lon
//        string item;
//        stringstream ss(line);
//        getline(ss, item, separator);
//        lat = atof(item.c_str());
//        getline(ss, item, separator);
//        lon = atof(item.c_str());

//        if(lat != 0.0 && lon != 0.0) //valid points
//        {
//            //convert to path
//            //std::cerr << lat << ", " << lon << std::endl;
//            vector<int16_t> path = Tile::fromDegrees(DegreesPoint(lon,lat), quadtreeDepth).path();

//            Node* currentNode = quadtreeRoot;

//            //increase counter
//            currentNode->objectCount++;

//            for(auto i = 0; i < quadtreeDepth; i++)
//            {
//                switch(path[i])
//                {
//                    case 0:
//                        if(currentNode->a == NULL)
//                            currentNode->a = new Node(currentNode, 0);

//                        currentNode = currentNode->a;
//                        break;
//                    case 1:
//                        if(currentNode->b == NULL)
//                            currentNode->b = new Node(currentNode, 1);

//                        currentNode = currentNode->b;
//                        break;
//                    case 2:
//                        if(currentNode->c == NULL)
//                            currentNode->c = new Node(currentNode, 2);

//                        currentNode = currentNode->c;
//                        break;
//                    case 3:
//                        if(currentNode->d == NULL)
//                            currentNode->d = new Node(currentNode, 3);

//                        currentNode = currentNode->d;
//                        break;
//                }

//                //increase counter
//                currentNode->objectCount++;
//            }
//        }
//    }

//    return quadtreeRoot;
//}


//vector<uint64_t> testDistrubution(string FileName, char separator, Node* quadtreeRoot)
//{
//    double lat, lon;
//    ifstream txtFile(FileName);

//    PartitionFunction* partitionFunction = new PartitionFunction(quadtreeRoot);

//    vector<uint64_t> counts;
//    for(int i = 0; i < partitionFunction->numThreads; i++)
//        counts.push_back(0);

//    //read tsv file line by line
//    for(string line; getline(txtFile, line); )
//    {
//        //extract lat and lon
//        string item;
//        stringstream ss(line);
//        getline(ss, item, separator);
//        lat = atof(item.c_str());
//        getline(ss, item, separator);
//        lon = atof(item.c_str());

//        if(lat != 0.0 && lon != 0.0) //valid points
//        {
//            //convert to path
//            //std::cerr << lat << ", " << lon << std::endl;
//            vector<int16_t> path = Tile::fromDegrees(DegreesPoint(lon,lat), quadtreeDepth).path();

//            auto n = path.size();
//            AddressType result = 0;
//            for (int i = n - 1; i >= 0; --i)
//            {
//                auto lbl = path[i];
//                //result = result + ((lbl & 0x3) << 2*i);
//                result = (result << 2) + (lbl & 0x3);
//            }

//            int thread_number = partitionFunction->getThreadIdForAddress(result, quadtreeDepth);
//            ++counts[thread_number];
//        }
//    }

//    return counts;
//}



//
//
//
std::size_t random(std::size_t n) {
    static std::random_device rd;
    static std::mt19937       gen(rd());
    std::uniform_int_distribution<std::size_t> dis(0, n-1);
    return dis(gen);
}

//-----------------
// ShuffleIterator
//-----------------

template <typename T>
struct ShuffleIterator {
public:
    ShuffleIterator(std::vector<T> &list);
    bool next(T& output);
public:
    std::vector<T> &list;
    std::size_t index { 0 };
};

template <typename T>
ShuffleIterator<T>::ShuffleIterator(std::vector<T> &list):
    list(list)
{}

template <typename T>
bool ShuffleIterator<T>::next(T &output)
{
    auto n = std::distance(list.begin() + index, list.end());
    if (n == 0)
        return false;
    auto i = random(n);
    std::swap(*(list.begin() + index), *(list.begin() + index + i));
    output = list[index];
    ++index;
    return true;
}

//-----------------------------------------------------------------
// main
//-----------------------------------------------------------------

struct Sample {
public:
    Sample() = default;
    void push(double v);
    double mean() const;
    double stddev() const;
    double min() const;
    double max() const;
    int size() const;
public:
    int    _size { 0 };
    double _min { 0 };
    double _max { 0 };
    double _sum { 0 };
    double _sum2 { 0 };
};

void Sample::push(double v) {
    if (_size == 0) {
        _min = _max = _sum = v;
        _sum2 = v * v;
    }
    else {
        _min = std::min(_min,v);
        _max = std::max(_max,v);
        _sum += v;
        _sum2 += v * v;
    }
    ++_size;
}

double Sample::mean() const {
    return _size ? _sum / _size : 0.0;
}

double Sample::stddev() const {
    auto m = mean();
    return _size ? sqrt(_sum2/_size - m*m) : 0.0;
}

double Sample::min() const {
    return _min;
}

double Sample::max() const {
    return _max;
}

int Sample::size() const {
    return _size;
}

std::ostream& operator<<(std::ostream& os, const Sample& sample) {
    os << "size:   " << sample.size() << std::endl;
    os << "min:    " << sample.min() << std::endl;
    os << "max:    " << sample.max() << std::endl;
    os << "mean:   " << sample.mean() << std::endl;
    os << "stddev: " << sample.stddev() << std::endl;
    return os;
}

//-----------------------------------------------------------------
// main
//-----------------------------------------------------------------

int main(int argc, char** args)
{
//    std::vector<std::string> argv()
    Options options(std::vector<std::string>{args, args + argc});

    std::ofstream estream("qtpart.log");

    std::vector<DegreesPoint> points;

    // read point into memory
    {
        std::ifstream is(options.input.getValue());
        std::string line;
        int line_no = 0;
        while (std::getline(is, line)) {
            ++line_no;
            try {
                std::stringstream ss(line);
                std::string token;
                std::getline(ss, token, '|');
                double lat = std::stod(token);
                std::getline(ss, token, '|');
                double lon = std::stod(token);
                points.push_back({lon,lat});
            }
            catch (...) {
                estream << "[Warning] could not parse lat lon on line " << line_no << std::endl;
            }
        }
    }

    //
    // Create a quadtree with n random points
    // from the input file
    //
    quadtree::QuadTree quadtree;
    ShuffleIterator<DegreesPoint> iter(points);
    DegreesPoint p;
    int actual_training_points = 0;
    for (int i=0; iter.next(p) && i<options.training_size.getValue();++i) {
        auto tile = Tile::fromDegrees(p,25);
        quadtree::Path path(tile.x,tile.y,tile.z);
        // std::cout << "inserting point at " << path << std::endl;
        quadtree.insert(path);
        ++actual_training_points;
    }


    //
    // initialize partition function
    //

    partition_function::PartitionFunction<quadtree::Path> pfunc(
                    options.num_parts.getValue(),
                    actual_training_points
                );
    quadtree::Iterator iterator(quadtree);
    quadtree::ConstNodePtr node;
    while ((node=iterator.next())) {
        // std::cerr << "leaf at address: " << node->path() << std::endl;
        pfunc.push(node->path(), node->objectCount);
    }

    //
    // test with all the points
    //
    std::map<int,int> distribution;
    for (auto p: points) {
        auto tile = Tile::fromDegrees(p,25);
        quadtree::Path path { tile.x, tile.y, tile.z };
        auto part = pfunc.part(path);
        ++distribution[part];
    }

    // report numbers
    std::cout << "Summary" << std::endl;
    std::cout << "Total Points:      " << points.size() << std::endl;
    std::cout << "Training Set Size: " << options.training_size.getValue() << std::endl;

    Sample sample;
    for (auto &it: distribution) {
        auto part  = it.first;
        auto count = it.second;
        sample.push(count);
        std::cout << "part[" << std::setw(2) << part << "] -> " << std::setw(10) << count << std::endl;
    }

    std::cout << sample << std::endl;




//    Node* quadtreeRoot = generateCountQuadtree(*(args + sizeof(char)), '|'); //generateTestQuadtree();// generateCountQuadtree(*(args + sizeof(char)), '|');
//    vector<uint64_t> counts = testDistrubution(*(args + sizeof(char)), '|', quadtreeRoot);
//    return 0;

}
