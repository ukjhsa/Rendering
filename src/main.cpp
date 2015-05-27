#include <cstdlib>
#include <ctime>
#include "Rendering.h"

int main(int argc, char* argv[])
{
    // x: 0 - 12.8
    // y: 0 - 12.8
    // z: 5 - 10
    // r: 1 - 3

    std::srand(std::time(nullptr));

    Rendering rendering;
    rendering.read_model("model.txt");
    rendering.set_camera(Point(6.4, 6.4, -10));
    rendering.add_light_source(Point(6.4, -10, 10));

    rendering.set_image_resolution(256, 256, 0.05);

    rendering.raytracing();

    rendering.export_image("output.ppm");

    return EXIT_SUCCESS;
}
