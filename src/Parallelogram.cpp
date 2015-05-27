#include <cmath>
#include <limits>
#include "Ray.h"
#include "Model.h"
#include "Parallelogram.h"

Parallelogram::Parallelogram()
    : Parallelogram(Point(), Vector(), Vector())
{
}

Parallelogram::Parallelogram(const Point& vertex, const Vector& u, const Vector& v,
                             const Color& object, const Color& light,
                             double ambient, double diffuse, double specular,
                             double reflection, double refraction, double refractive_index)
    : Model(object, light,
            ambient, diffuse, specular,
            reflection, refraction, refractive_index),
      vertex_(vertex), u_(u), v_(v)
{
}

Vector Parallelogram::normal(const Vector& incident, const Point& point) const
{
    Vector N = u_.cross_product(v_);
    if (N.dot_product(incident) > 0) {
        N = -N;
    }
    return N.normalized();
}

double Parallelogram::intersect(const Ray& incident) const
{
    // vertex + s1 * u + s2 * v == start + t * dir
    //
    // => s1 [u] + s2 [v] - t [dir] = -[vertex] + [start]
    //
    //        a b c | p
    //        d e f | q
    //        g h i | r

    double a = u_.x();
    double b = v_.x();
    double c = -incident.dir().x();
    double p = -vertex_.x() + incident.start().x();

    double d = u_.y();
    double e = v_.y();
    double f = -incident.dir().y();
    double q = -vertex_.y() + incident.start().y();

    double g = u_.z();
    double h = v_.z();
    double i = -incident.dir().z();
    double r = -vertex_.z() + incident.start().z();

    double detA = (a*e*i + b*f*g + c*d*h) -
                    (c*e*g+a*f*h+b*d*i);
    double detX = (p*e*i + b*f*r + c*q*h) -
                    (c*e*r+p*f*h+b*q*i);
    double detY = (a*q*i + p*f*g + c*d*r) -
                    (c*q*g+a*f*r+p*d*i);
    double detZ = (a*e*r + b*q*g + p*d*h) -
                    (p*e*g+a*q*h+b*d*r);

    double epsilon = std::numeric_limits<double>::epsilon();
    // detA is must NOT be zero
    if (fabs(detA) > epsilon) {
        double s1 = detX / detA;
        double s2 = detY / detA;
        double t = detZ / detA;
        if ((fabs(s1) < epsilon || epsilon < s1) && (fabs(s1-1) < epsilon || (s1+epsilon) < 1) &&
            (fabs(s2) < epsilon || epsilon < s2) && (fabs(s2-1) < epsilon || (s2+epsilon) < 1))
            return t;
    }
    return -1;
}

Color Parallelogram::ambient() const
{
    return Model::ambient();
}

Color Parallelogram::diffuse(const Ray& incident, const Point& point, const Point& light) const
{
    Vector L = (light-point).normalized();
    //std::cout << "L: " << L << std::endl;
    Vector N = normal(incident.dir(), point);
    //std::cout << "N: " << N << std::endl;
    double dotLN = std::max(L.dot_product(N), 0.0);
    return diffuse_ * dotLN * object_;
}

Color Parallelogram::specular(const Ray& incident, const Point& point, const Point& light) const
{
    Vector L = (light-point).normalized();
    Vector N = normal(incident.dir(), point);
    double dotLN = std::max(L.dot_product(N), 0.0);

    Vector V = -incident.dir();
    //std::cout << "V: " << V << std::endl;
    Vector R = (2 * dotLN * N - L).normalized();
    //std::cout << "R: " << R << std::endl;
    double dotRV = std::max(R.dot_product(V), 0.0);
    return specular_ * std::pow(dotRV, 10.0) * light_;
}

Color Parallelogram::calc_phonglighting(const Ray& incident, const Point& point, const Point& light) const
{
    return Model::calc_phonglighting(incident, point, light);
}
