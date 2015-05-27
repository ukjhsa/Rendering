#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>
#include <ctime>
#include <chrono>
#include <iostream>
#include "Color.h"
#include "Point.h"
#include "Ray.h"
#include "Light.h"
#include "Sphere.h"
#include "Parallelogram.h"
#include "Triangle.h"
#include "PPMImage.h"
#include "Rendering.h"

void Rendering::read_model(const std::string& file_name)
{
    std::ifstream ifs(file_name);
    if (ifs.is_open()) {
        while (ifs.good()) {
            std::string line;
            std::getline(ifs, line);
            std::stringstream ss(line);
            ss >> line;
            if (line == "//") {
                // ignore
            }
            else if (line == "sphere") {
                Point center;
                ss >> center;
                double r = 0;
                ss >> r;
                Color object, light;
                ss >> object >> light;
                double ambient = 0, diffuse = 0, specular = 0;
                ss >> ambient >> diffuse >> specular;
                double reflectance = 0, transmittance = 0, refractive_index = 0;
                ss >> reflectance >> transmittance >> refractive_index;

                models_.push_back(
                            std::make_shared<Sphere>(
                                center, r,
                                object, light,
                                ambient, diffuse, specular,
                                reflectance, transmittance, refractive_index));
            }
            else if (line == "parallelogram") {
                Point vertex;
                Vector u, v;
                ss >> vertex >> u >> v;
                Color object, light;
                ss >> object >> light;
                double ambient = 0, diffuse = 0, specular = 0;
                ss >> ambient >> diffuse >> specular;
                double reflectance = 0, transmittance = 0, refractive_index = 0;
                ss >> reflectance >> transmittance >> refractive_index;

                models_.push_back(
                            std::make_shared<Parallelogram>(
                                vertex, u, v,
                                object, light,
                                ambient, diffuse, specular,
                                reflectance, transmittance, refractive_index));
            }
            else if (line == "triangle") {
                Point vertex;
                Vector u, v;
                ss >> vertex >> u >> v;
                Color object, light;
                ss >> object >> light;
                double ambient = 0, diffuse = 0, specular = 0;
                ss >> ambient >> diffuse >> specular;
                double reflectance = 0, transmittance = 0, refractive_index = 0;
                ss >> reflectance >> transmittance >> refractive_index;

                models_.push_back(
                            std::make_shared<Triangle>(
                                vertex, u, v,
                                object, light,
                                ambient, diffuse, specular,
                                reflectance, transmittance, refractive_index));
            }
            else {
                break;
            }
        }
    }
}

void Rendering::set_camera(const Point& camera)
{
    camera_ = camera;
}

void Rendering::add_light_source(const Point& light)
{
    lights_.push_back(std::make_shared<AreaLight>(light));
}

void Rendering::set_image_resolution(int row, int col,
                                     double ratio_resolution_to_scene)
{
    this->image_row_ = row;
    this->image_col_ = col;
    this->ratio_resolution_to_scene_ = ratio_resolution_to_scene;
}

void Rendering::export_image(const std::string& file_name)
{
    image_.export_image(file_name);
}

void Rendering::raytracing()
{
    image_.init(image_row_, image_col_);

    auto start_time = std::chrono::system_clock::now();

    for (int row = 0; row < image_row_; ++row) {
        for (int col = 0; col < image_col_; ++col) {

            // row is coordinate y, col is coordinate x
            Point imagep = Point(col * ratio_resolution_to_scene_,
                                 row * ratio_resolution_to_scene_,
                                 -1);
            Vector dir = (imagep-camera_).normalized();
            // record closest sphere
            // simply use max z value as MAX

            Color c = trace(Ray(camera_, dir), 3);
            image_.write_pixel(row, col, c);
        }
    }

    auto end_time = std::chrono::system_clock::now();
    auto timeExecution =
        std::chrono::duration_cast<std::chrono::milliseconds>(
                                            end_time - start_time).count();

    std::cout << "time: " << timeExecution << std::endl;
}

Color Rendering::trace(const Ray& ray, int times) const
{
    if (times <= 0) {
        return Color(0, 0, 0);
    }
    else {
        // find the closest Model
        double closest_model_distance = 0;
        std::shared_ptr<Model> closest_model;
        find_closest_model(closest_model_distance, closest_model, ray);

        // if it does NOT detect any object
        if (closest_model) {
            return calc_color(ray, times, ray.target(closest_model_distance), closest_model);
        }
        else {
            return Color(0, 0, 0);
        }
    }
}

void Rendering::find_closest_model(double& distance, std::shared_ptr<Model>& model, const Ray& ray) const
{
    double closest_distance = std::numeric_limits<double>::max();
    std::shared_ptr<Model> closest_model;
    for (auto& m : models_) {
        //if (m != self_object) {
            double d = m->intersect(ray);
            if (d > std::numeric_limits<double>::epsilon() &&
                d < closest_distance &&
                ray.start().distance(ray.target(d)) > DIFFERENT_POINT) {
                closest_distance = d;
                closest_model = m;
            }
        //}
    }
    distance = closest_distance;
    model = closest_model;
}

Color Rendering::calc_color(const Ray& ray, int times, const Point& point, const std::shared_ptr<Model>& model) const
{
    Color c(0, 0, 0);

    for (auto& l : lights_) {

        c += calc_color_of_object(ray, point, l, model);
    }
    // reflection
    c += calc_color_of_reflection(ray, point, model, times);

    // refraction
    c += calc_color_of_refraction(ray, point, model, times);

    return c;
}

Color Rendering::calc_color_of_object(const Ray& ray, const Point& point, const std::shared_ptr<Light>& light, const std::shared_ptr<Model>& model) const
{
    unsigned int r = 0, g = 0, b = 0;
    for (int i = 0; i < light->sample(); ++i) {
        Point locLight = light->location();

        Vector N = model->normal(ray.dir(), point);
        Vector L = (locLight-point).normalized();
        double dotNL = N.dot_product(L);

        Color c;
        if (dotNL < 0 || is_in_shadow(Ray(point, L), model)) {
            c += model->ambient();
        }
        else {
            // Phong lighting
            c += model->calc_phonglighting(ray, point, locLight);
        }
        r += c.R(); g += c.G(); b += c.B();
    }
    r /= light->sample();
    g /= light->sample();
    b /= light->sample();
    return Color(r, g, b);
}

bool Rendering::is_in_shadow(const Ray& ray, const std::shared_ptr<const Model>& model) const
{
    double shadow_distance = 0;
    std::shared_ptr<Model> shadow_model;
    find_closest_model(shadow_distance, shadow_model, ray);

    if (shadow_model) {
        return true;
    }
    else {
        return false;
    }
}

Color Rendering::calc_color_of_reflection(const Ray& incident, const Point& point, const std::shared_ptr<Model>& model, int times) const
{
    unsigned int r = 0, g = 0, b = 0;
    for (int i = 0; i < model->sample; ++i) {
        Ray reflected = model->calc_random_reflected_ray(incident, point);
        Color c = model->reflectance() * trace(reflected, times-1);
        r += c.R(); g += c.G(); b += c.B();
    }

    r /= model->sample;
    g /= model->sample;
    b /= model->sample;
    return Color(r, g, b);
}

Color Rendering::calc_color_of_refraction(const Ray& incident, const Point& point, const std::shared_ptr<Model>& model, int times) const
{
    Ray refracted = model->calc_refracted_ray(incident, point);

    if (refracted.is_valid()) {
        return model->transmittance() * trace(refracted, times-1);
    }
    else {
        return Color();
    }
}
