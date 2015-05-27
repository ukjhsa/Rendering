#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray
{
public:
    Ray();
    Ray(const Point& start, const Vector& direction,
        double refractive_index = 1.0);
    Ray(const Ray& rhs) = default;



/**
\brief Return the start point.
*/
    Point start() const { return start_; }
/**
\brief Return the direction vector.
*/
    Vector dir() const { return direction_; }
/**
\brief Return the refractive index.
*/
    double refractive_index() const { return refractive_index_; }



/**
\brief Calculate the target point according to the parameter along the current ray.
*/
    Point target(double parameter) const;
/**
\brief Change the refractive index.
*/
    void changeRefractiveIndex(double refractive_index);
/**
\brief Check the ray is valid.
\return True if the direction is not zero.
*/
    bool is_valid() const;



/**
\brief Get the opposite ray.
*/
    Ray operator-() const;

private:
    Point start_;
    Vector direction_;
    double refractive_index_;
};

#endif // RAY_H
