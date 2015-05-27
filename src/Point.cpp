#include <cmath>
#include <limits>
#include <istream>
#include "Point.h"

Point::Point(double x, double y, double z) : x_(x), y_(y), z_(z)
{
}

double Point::distance(const Point& rhs) const
{
    return std::sqrt((x_-rhs.x()) * (x_-rhs.x()) +
                     (y_-rhs.y()) * (y_-rhs.y()) +
                     (z_-rhs.z()) * (z_-rhs.z()));
}

bool Point::operator==(const Point& rhs) const
{
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(x_ - rhs.x_) < epsilon &&
           std::abs(y_ - rhs.y_) < epsilon &&
           std::abs(z_ - rhs.z_) < epsilon;
}

bool Point::operator!=(const Point& rhs) const
{
    return !(operator==(rhs));
}

std::istream& operator>> (std::istream& is, Point& p)
{
    double x = 0, y = 0, z = 0;
    is >> x >> y >> z;
    p = Point(x, y, z);
    return is;
}
