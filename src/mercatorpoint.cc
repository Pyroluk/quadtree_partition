#include "mercatorpoint.hh"

#include <sstream>
#include <iostream>
#include <math.h>

MercatorPoint::MercatorPoint(double x, double y)
{
    this->x = x;
    this->y = y;
}

std::string MercatorPoint::toString()
{
    std::stringstream ss;
    ss << "Mercator[" << x << "], [" << y << "]";
    return ss.str();
}

DegreesPoint MercatorPoint::toDegrees()
{
    return DegreesPoint(this->x * 180.0, atan(sinh(this->y * M_PI)) / (M_PI / 180.0));
}
