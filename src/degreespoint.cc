#include "degreespoint.hh"
#include <sstream>
#include <cmath>
// #include <boost/lexical_cast.hpp>

DegreesPoint::DegreesPoint(double x, double y):
    x(x), y(y)
{}

std::string DegreesPoint::toString()
{
    std::stringstream ss;
    ss << "Degrees[" << x << "], [" << y << "]";
    return ss.str();
}

MercatorPoint DegreesPoint::toMercator()
{
    return MercatorPoint(this->x / 180.0, log(tan((this->y * M_PI/180.0)/2.0 + M_PI/4.0)) / M_PI);
}
