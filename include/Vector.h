#ifndef VECTOR_H
#define VECTOR_H

#include <istream>

class Vector
{
public:

    Vector() = default;
    Vector(double x, double y, double z);
    Vector(const Vector& rhs) = default;



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
\brief Equality

Two vectors are said to be equal if they have the same magnitude and direction.
So two Vectors (a,b,c), (x,y,z) are equal if a==x && b==y && c==z

\return true if two Vectors are same, otherwise false.
*/
    bool is_equal(const Vector& rhs) const;
/**
\brief Opposite vector.
*/
    bool is_opposite(const Vector& rhs) const;
/**
\brief Parallel vector.
*/
    bool is_parallel(const Vector& rhs) const;
/**
\brief Scalar multiplication
*/
    Vector scalar_multiplication(double scalar) const;
/**
\brief Length

The length or magnitude or norm of the vector.
*/
    double length() const;
/**
\brief Normalized vector or unit vector
*/
    Vector normalized() const;
/**
\brief Check whether the Vector is the zero vector.
*/
    bool is_zero() const;



/**
\brief Dot product
*/
    double dot_product(const Vector& rhs) const;
/**
\brief Cross product

Let  c = a X b
=> (c1, c2, c3) = (a1, a2, a3) X (b1, b2, b3)
    c1 = a2b3-a3b2
=>  c2 = a3b1-a1b3
    c3 = a1b2-a2b1
*/
    Vector cross_product(const Vector& rhs) const;



/**
\brief Check whether two Vectors are same.
\sa is_equal
*/
    bool operator==(const Vector& rhs) const;
/**
\brief Check whether two Vectors are different.
*/
    bool operator!=(const Vector& rhs) const;



/**
\brief Vector addition
*/
    Vector operator+(const Vector& rhs) const;
/**
\brief Vector subtraction
*/
    Vector operator-(const Vector& rhs) const;
/**
\brief Vector inversion
*/
    Vector operator-() const;

private:

    double x_, y_, z_;
};

Vector operator*(double scalar, const Vector& rhs);
Vector operator*(const Vector& lhs, double scalar);

class Point;

Vector operator-(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Vector& rhs);



std::istream& operator>> (std::istream& is, Vector& v);

#endif // VECTOR_H
