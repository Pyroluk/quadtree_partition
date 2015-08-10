#pragma once

#include "degreespoint.hh"

class DegreesPoint;//forward declaration

class MercatorPoint
{
    public:
        double x;
        double y;

        MercatorPoint(double x, double y);
        std::string toString();
        DegreesPoint toDegrees();
};

