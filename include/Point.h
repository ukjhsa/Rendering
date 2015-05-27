#ifndef POINT_H
#define POINT_H

#include <istream>

class Point
{
public:
    Point() = default;
    Point(double x, double y, double z);
    Point(const Point& rhs) = default;



/**
\brief Get the coordinate x
*/
    double x() const { return x_; }
/**
\brief Get the coordinate y
*/
    double y() const { return y_; }
/**
\brief Get the coordinate z
*/
    double z() const { return z_; }



/**
\brief Calculate the Euclidean distance of two Points.
*/
    double distance(const Point& rhs) const;



/**
\brief Check whether two Points are same.
\return true if two Points are same, otherwise false.
*/
    bool operator==(const Point& rhs) const;
/**
\brief Check whether two Points are different.
\return true if two Points are different, otherwise false.
*/
    bool operator!=(const Point& rhs) const;



private:
    double x_, y_, z_;
};

std::istream& operator>> (std::istream& is, Point& p);

#endif // POINT_H
