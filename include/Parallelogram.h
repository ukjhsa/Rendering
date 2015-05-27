#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Model.h"
#include "Point.h"
#include "Color.h"

class Ray;

class Parallelogram : public Model
{
public:
    Parallelogram();
    Parallelogram(const Point& vertex, const Vector& u, const Vector& v,
                  const Color& object = Color(), const Color& light = Color(),
                  double ambient = 0, double diffuse = 0, double specular = 0,
                  double reflection = 0, double refraction = 0, double refractive_index = 0);
    ~Parallelogram() = default;

    Vector normal(const Vector& incident, const Point& point) const override;
    double intersect(const Ray& incident) const override;

    Color ambient() const override;
    Color diffuse(const Ray& incident, const Point& point, const Point& light) const override;
    Color specular(const Ray& incident, const Point& point, const Point& light) const override;
    Color calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const override;

    const Point& vertex() const { return vertex_; }
    const Vector& u() const { return u_; }
    const Vector& v() const { return v_; }

private:
    Point vertex_;
    Vector u_, v_;
};

#endif // PARALLELOGRAM_H
