#include "Point.h"
#include "Vector.h"
#include "Ray.h"

Ray::Ray() : Ray(Point(), Vector())
{
}

Ray::Ray(const Point& start, const Vector& direction, double refractive_index) :
    start_(start), direction_(direction), refractive_index_(refractive_index)
{
}

Point Ray::target(double parameter) const
{
    return start_ + parameter * direction_;
}

void Ray::changeRefractiveIndex(double refractive_index)
{
    refractive_index_ = refractive_index;
}

bool Ray::is_valid() const
{
    return direction_ != Vector();
}

Ray Ray::operator-() const
{
    return Ray(start_, -direction_);
}
