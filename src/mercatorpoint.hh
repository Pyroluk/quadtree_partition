#pragma once

#include "degreespoint.hh"

class DegreesPoint;//forward declaration

class MercatorPoint
{
public:
    MercatorPoint(double x, double y);
    std::string toString();
    DegreesPoint toDegrees();
public:
    double x;
    double y;
};

