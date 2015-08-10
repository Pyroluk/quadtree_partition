#pragma once

#include <string>

#include "mercatorpoint.hh"

class MercatorPoint;//forward declaration

class DegreesPoint
{
    public:
        int x;
        int y;

        DegreesPoint(double x, double y);

        std::string toString();

        MercatorPoint toMercator();
};
