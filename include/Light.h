#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"

class Light
{
public:
    Light(const Point& location);
    Light(const Light& rhs) = default;
    virtual ~Light() = default;



/**
\brief Return the location.
*/
    virtual Point location() const { return location_; }
/**
\brief Return the number of samples used by distributed ray tracing.
*/
    virtual int sample() const { return 1; }

protected:
    Point location_;
};

class AreaLight : public Light
{
public:
    AreaLight(const Point& location);
    AreaLight(const AreaLight& rhs) = default;
    virtual ~AreaLight() = default;

    virtual Point location() const override;

    virtual int sample() const override { return 32; }

private:
    double radius = 4;
};

#endif // LIGHT_H
