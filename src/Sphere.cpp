#include <cmath>
#include <iostream>
#include <algorithm>
#include "Point.h"
#include "Ray.h"
#include "Model.h"
#include "Sphere.h"

Sphere::Sphere() : Sphere(Point(), 0.0)
{
}

Sphere::Sphere(const Point& center, double radius,
               const Color& object, const Color& light,
               double ambient, double diffuse, double specular,
               double reflection, double refraction, double refractive_index)
    : Model(object, light,
              ambient, diffuse, specular,
              reflection, refraction, refractive_index),
      center_(center), radius_(radius)
{
}

Sphere::~Sphere()
{
}

void Sphere::create(const Point& center, double radius)
{
    center_ = center;
    radius_ = radius;
}

Vector Sphere::normal(const Vector& incident, const Point& point) const
{
    return (point - center_).normalized();
}

double Sphere::intersect(const Ray& incident) const
{
    // ray = start + scalar * dir,
    // replace into (x-center.x)^2 + (y-center.y)^2 + (z-center.z)^2 = r^2,
    // then solve scalar
    Point s = incident.start();
    Vector dir = incident.dir();

    double a = dir.x()*dir.x() + dir.y()*dir.y() + dir.z()*dir.z();
    double b = 2 * (s.x()*dir.x() + s.y()*dir.y() + s.z()*dir.z() -
            dir.x()*center_.x()-dir.y()*center_.y()-dir.z()*center_.z());
    double c = s.x()*s.x() + s.y()*s.y() + s.z()*s.z() +
        center_.x()*center_.x()+center_.y()*center_.y()+center_.z()*center_.z() -
        2*(s.x()*center_.x()+s.y()*center_.y()+s.z()*center_.z()) -
        radius_*radius_;

    double express = b * b - 4.0 * a * c;

    double epsilon = std::numeric_limits<double>::epsilon();
    if (fabs(a) > epsilon && (express > epsilon || fabs(express) < epsilon)) {
        return (-b - sqrt(express)) / (2.0 * a);
    }
    else {
        return -1;
    }
}

Color Sphere::ambient() const
{
    return Model::ambient();
}

Color Sphere::diffuse(const Ray& incident, const Point& point, const Point& light) const
{
    Vector L = (light-point).normalized();
    Vector N = normal(incident.dir(), point);

    double dotLN = std::max(L.dot_product(N), 0.0);

    return diffuse_ * dotLN * object_;
}

Color Sphere::specular(const Ray& incident, const Point& point, const Point& light) const
{
    Vector L = (light-point).normalized();
    Vector N = normal(incident.dir(), point);
    double dotLN = std::max(L.dot_product(N), 0.0);

    Vector V = -incident.dir();
    Vector R = (2 * dotLN * N - L).normalized();

    double dotRV = std::max(R.dot_product(V), 0.0);

    return specular_ * pow(dotRV, 10.0) * light_;
}

Color Sphere::calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const
{
    return Model::calc_phonglighting(incident, point, light);
}
