#ifndef SPHERE_H
#define SPHERE_H

#include "Model.h"
#include "Point.h"
#include "Color.h"

class Ray;

class Sphere : public Model
{
public:
    Sphere();
    Sphere(const Point& center, double radius,
           const Color& object = Color(), const Color& light = Color(),
           double ambient = 0, double diffuse = 0, double specular = 0,
           double reflection = 0, double refraction = 0, double refractive_index = 0);
    ~Sphere();

    void create(const Point& center, double radius);

    Vector normal(const Vector& incident, const Point& point) const override;
    double intersect(const Ray& incident) const override;

    const Point& center() const { return center_; }
    double radius() const { return radius_; }

    Color ambient() const override;
    Color diffuse(const Ray& incident, const Point& point, const Point& light) const override;
    Color specular(const Ray& incident, const Point& point, const Point& light) const override;
    Color calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const override;

private:
    Point center_;
    double radius_;
};

#endif // SPHERE_H
