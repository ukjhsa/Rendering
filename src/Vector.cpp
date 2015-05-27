#include <cmath>
#include <limits>
#include <istream>
#include "Vector.h"
#include "Point.h"

Vector::Vector(double x, double y, double z) : x_(x), y_(y), z_(z)
{
}

bool Vector::is_equal(const Vector& rhs) const
{
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(x_ - rhs.x_) < epsilon &&
           std::abs(y_ - rhs.y_) < epsilon &&
           std::abs(z_ - rhs.z_) < epsilon;
}

bool Vector::is_opposite(const Vector& rhs) const
{
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(x_ + rhs.x_) < epsilon &&
           std::abs(y_ + rhs.y_) < epsilon &&
           std::abs(z_ + rhs.z_) < epsilon;
}

bool Vector::is_parallel(const Vector& rhs) const
{
    Vector cross = cross_product(rhs);
    return cross.is_zero();
}

Vector Vector::scalar_multiplication(double scalar) const
{
    return Vector(scalar * x_, scalar * y_, scalar * z_);
}

double Vector::length() const
{
    return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
}

Vector Vector::normalized() const
{
    double norm = length();
    return Vector(x_ / norm, y_ / norm, z_ / norm);
}

bool Vector::is_zero() const
{
    double epsilon = std::numeric_limits<double>::epsilon();
    return std::abs(x_) < epsilon &&
           std::abs(y_) < epsilon &&
           std::abs(z_) < epsilon;
}

double Vector::dot_product(const Vector& rhs) const
{
    return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
}

Vector Vector::cross_product(const Vector& rhs) const
{
    return Vector(y_ * rhs.z_ - z_ * rhs.y_,
                  z_ * rhs.x_ - x_ * rhs.z_,
                  x_ * rhs.y_ - y_ * rhs.x_);
}

bool Vector::operator==(const Vector& rhs) const
{
    return is_equal(rhs);
}

bool Vector::operator!=(const Vector& rhs) const
{
    return ! (operator==(rhs));
}

Vector Vector::operator+(const Vector& rhs) const
{
    return Vector(x_ + rhs.x_,
                  y_ + rhs.y_,
                  z_ + rhs.z_);
}

Vector Vector::operator-(const Vector& rhs) const
{
    return Vector(x_ -rhs.x_,
                  y_ -rhs.y_,
                  z_ -rhs.z_);
}

Vector Vector::operator-() const
{
    return Vector(-x_, -y_, -z_);
}

Vector operator*(double scalar, const Vector& rhs) {
    return rhs.scalar_multiplication(scalar);
}

Vector operator*(const Vector& lhs, double scalar) {
    return lhs.scalar_multiplication(scalar);
}

Vector operator-(const Point& lhs, const Point& rhs)
{
    return Vector(lhs.x() - rhs.x(),
                  lhs.y() - rhs.y(),
                  lhs.z() - rhs.z());
}

Point operator+(const Point& lhs, const Vector& rhs)
{
    return Point(lhs.x() + rhs.x(),
                 lhs.y() + rhs.y(),
                 lhs.z() + rhs.z());
}

std::istream& operator>>(std::istream& is, Vector& v)
{
    double x = 0, y = 0, z = 0;
    is >> x >> y >> z;
    v = Vector(x, y, z);
    return is;
}
