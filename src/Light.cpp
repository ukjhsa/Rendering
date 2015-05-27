#include <random>
#include "Point.h"
#include "Vector.h"
#include "Light.h"

Light::Light(const Point& location) : location_(location)
{
}

AreaLight::AreaLight(const Point& location) : Light(location)
{
}

Point AreaLight::location() const
{
    static std::mt19937 gen(rand());
    static std::uniform_real_distribution<> rnd;
    Vector r = Vector(rnd(gen) * 2 * radius - radius,
                      rnd(gen) * 2 * radius - radius,
                      rnd(gen) * 2 * radius - radius);
    return location_ + r;
}
