#ifndef RENDERING_H
#define RENDERING_H

#include <string>
#include <vector>
#include <memory>
#include "Point.h"
#include "PPMImage.h"

class Ray;
class Light;
class Model;
class Color;

/**
http://en.wikipedia.org/wiki/Rendering_%28computer_graphics%29
http://en.wikipedia.org/wiki/Ray_tracing_(graphics)
*/
class Rendering
{
public:
    Rendering() = default;
    Rendering(const Rendering& rhs) = default;
    ~Rendering() = default;



/**
\brief Read 3D model data.
*/
    void read_model(const std::string& file_name);
/**
\brief Set the position of camera (eye.)
*/
    void set_camera(const Point& camera);
/**
\brief Add the position of light source.
*/
    void add_light_source(const Point& light);



/**
\brief Specify the resolution of output image and its ratio to scene.
*/
    void set_image_resolution(int row, int col, double ratio_resolution_to_scene);
/**
\brief Export image to a file.
*/
    void export_image(const std::string& file_name);



/**
\brief Ray tracing
*/
    void raytracing();

private:
    Point camera_;
    std::vector<std::shared_ptr<Light>> lights_;
    std::vector<std::shared_ptr<Model>> models_;

    int image_row_, image_col_;
    double ratio_resolution_to_scene_;

    PPMImage image_;

    // the difference between two float point.
    // the value of epsilon is too small.
    static constexpr double DIFFERENT_POINT = 0.0000000001;

    Color trace(const Ray& ray, int times) const;

    void find_closest_model(double& distance, std::shared_ptr<Model>& model, const Ray& ray) const;
    bool is_in_shadow(const Ray& ray, const std::shared_ptr<const Model>& model) const;

    Color calc_color(const Ray& ray, int times, const Point& point, const std::shared_ptr<Model>& object) const;
    Color calc_color_of_object(const Ray& ray, const Point& point, const std::shared_ptr<Light>& light, const std::shared_ptr<Model>& object) const;
    Color calc_color_of_reflection(const Ray& incident, const Point& point, const std::shared_ptr<Model>& object, int times) const;
    Color calc_color_of_refraction(const Ray& incident, const Point& point, const std::shared_ptr<Model>& object, int times) const;

};

#endif // RENDERING_H
