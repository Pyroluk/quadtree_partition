#include "tile.hh"

#include <stdlib.h>
#include <sstream>


Tile::Tile(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Tile Tile::fromMercator(MercatorPoint p, int z)
{
    int size = 1 << z;
    int x_tile  = (1 + p.x)/2.0 * size;
    int y_tile  = (1 + p.y)/2.0 * size;
    return Tile(x_tile, y_tile, z);
}

Tile Tile::fromDegrees(DegreesPoint p, int z)
{
    return fromMercator(p.toMercator(), z);
}

MercatorPoint Tile::min()
{
    int size = 1 << this->z;
    double x = -1 + 2 * double(this->x)/double(size);
    double y = -1 + 2 * double(this->y)/double(size);
    return MercatorPoint(x,y);
}

MercatorPoint Tile::max()
{
    int size = 1 << this->z;
    int x = -1 + 2 * float(this->x + 1)/float(size);
    int y = -1 + 2 * float(this->y + 1)/float(size);
    return MercatorPoint(x, y);
}

MercatorPoint* Tile::bounds()
{
    MercatorPoint* minMax = (MercatorPoint*) malloc(sizeof(MercatorPoint) * 2);

    minMax[0] = this->min();
    minMax[1] = this->max();

    return minMax;
}

string Tile::toString()
{
    std::stringstream ss;
    ss << "Tile[x:" << x << ",y:" << y << ",z:" << z << "]";
    return ss.str();
}
