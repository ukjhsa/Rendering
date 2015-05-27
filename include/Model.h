#ifndef MODEL_H
#define MODEL_H

#include "Color.h"

class Point;
class Ray;
class Light;

class Model
{
public:
    Model();
    Model(const Color& object, const Color& light,
          double ambient, double diffuse, double specular,
          double reflectance, double transmittance, double refractive_index);
    virtual ~Model() = default;



/**
\brief Reflectance
*/
    virtual double reflectance() const { return reflectance_; }
/**
\brief Transmittance
*/
    virtual double transmittance() const { return transmittance_; }
/**
\brief Refractive index
*/
    virtual double refractive_index() const { return refractive_index_; }



/**
\brief The radius for Monte Carlo method in Distributed ray tracing.
*/
    const double radius = 0.1;
/**
\brief The number of samples for Monte Carlo method in Distributed ray tracing.
*/
    const int sample = 2;



/**
\brief Calculate the reflected ray.
*/
    virtual Ray calc_reflected_ray(const Ray& incident, const Point& point) const;
/**
\brief Calculate the reflected ray randomly.
*/
    virtual Ray calc_random_reflected_ray(const Ray& incident, const Point& point) const;
/**
\brief Calculate the refracted ray.

http://en.wikipedia.org/wiki/Refractive_index
http://en.wikipedia.org/wiki/Snell%27s_law
*/
    virtual Ray calc_refracted_ray(const Ray& incident, const Point& point) const;



/**
\brief Get the normal vector at point.
*/
    virtual Vector normal(const Vector& incident, const Point& point) const = 0;
/**
\brief Get the distance from start point of ray and
the intersect of incident ray and this model.
*/
    virtual double intersect(const Ray& incident) const = 0;



/**
\brief The ambient part in the Phong lighting.
*/
    virtual Color ambient() const;
/**
\brief The diffuse part in the Phong lighting.
*/
    virtual Color diffuse(const Ray& incident, const Point& point, const Point& light) const = 0;
/**
\brief The specular part in the Phong lighting.
*/
    virtual Color specular(const Ray& incident, const Point& point, const Point& light) const = 0;
/**
\brief Calculate the color according to the Phong lighting.
*/
    virtual Color calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const;

protected:
    Color object_, light_;
    double ambient_, diffuse_, specular_;
    double reflectance_, transmittance_, refractive_index_;
};

#endif // MODEL_H
