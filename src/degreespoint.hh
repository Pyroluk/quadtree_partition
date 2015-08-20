#pragma once

#include <string>

#include "mercatorpoint.hh"

class MercatorPoint;//forward declaration

class DegreesPoint
{
public:
    DegreesPoint() = default;
    DegreesPoint(double x, double y);
    std::string toString();
    MercatorPoint toMercator();
public:
    double x;
    double y;
};
