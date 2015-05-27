#include <cmath>
#include <limits>
#include <cstdlib>
#include <random>
#include "Color.h"
#include "Point.h"
#include "Ray.h"
#include "Light.h"
#include "Model.h"

Model::Model() :
    Model(Color(), Color(),
          0, 0, 0,
          0, 0, 0)
{
}

Model::Model(const Color& object, const Color& light,
             double ambient, double diffuse, double specular,
             double reflectance, double transmittance,
             double refractive_index) :
    object_(object), light_(light),
    ambient_(ambient), diffuse_(diffuse), specular_(specular),
    reflectance_(reflectance), transmittance_(transmittance),
    refractive_index_(refractive_index)
{
}

Ray Model::calc_reflected_ray(const Ray& incident, const Point& point) const
{
    Vector N = normal(incident.dir(), point);
    Vector project = -incident.dir().dot_product(N) * N;

    return Ray(point, (incident.dir() + 2 * project));
}

Ray Model::calc_random_reflected_ray(const Ray& incident, const Point& point) const
{
    Vector N = normal(incident.dir(), point);
    Vector project = -incident.dir().dot_product(N) * N;

    Vector reflected = incident.dir() + 2 * project;

    static std::mt19937 gen(rand());
    static std::uniform_real_distribution<> rnd;
    Vector r = Vector(rnd(gen) * 2 * radius - radius,
                      rnd(gen) * 2 * radius - radius,
                      rnd(gen) * 2 * radius - radius);

    return Ray(point, (reflected+r).normalized());
}

Ray Model::calc_refracted_ray(const Ray& incident, const Point& point) const
{
    double nIn = incident.refractive_index();
    double nOut = (std::abs(incident.refractive_index() - refractive_index_) <
                         std::numeric_limits<double>::epsilon()) ?
                              (1.0) : (refractive_index_);
    double n = nIn / nOut;

    Vector N = normal(incident.dir(), point);
    double cosIn = (-incident).dir().normalized().dot_product(N);
    double sinOut = n * std::sqrt(1.0 - cosIn * cosIn);

    if (sinOut > 1.0) {
        return Ray(point, Vector());
    }
    else {
        double cosOut = std::sqrt(1.0 - sinOut * sinOut);
        Vector dirOut = (n * incident.dir() + (n * cosIn - cosOut) * N).normalized();
        return Ray(point, dirOut, nOut);
    }
}

Color Model::ambient() const
{
    Color color(0, 0, 0);
    color += ambient_ * object_;
    return color;
}

Color Model::calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const
{
    return ambient() + diffuse(incident, point, light) + specular(incident, point, light);
}
