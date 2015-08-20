#pragma once

#include <vector>
#include <string>
#include "mercatorpoint.hh"
#include "degreespoint.hh"

using namespace std;

class Tile
{
    public:
        int x;
        int y;
        int z;

        Tile(int x, int y, int z);
        static Tile fromMercator(MercatorPoint p, int z);
        static Tile fromDegrees(DegreesPoint p, int z);

        MercatorPoint min();
        MercatorPoint max();

        MercatorPoint* bounds();
        std::string toString();
};

