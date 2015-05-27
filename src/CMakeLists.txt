cmake_minimum_required(VERSION 2.8.12)

# build library
set(rendering_source
                Rendering.cpp
                PPMImage.cpp
                Model.cpp
                Point.cpp
                Light.cpp
                Vector.cpp
                Ray.cpp
                Color.cpp
                Sphere.cpp
                Triangle.cpp
                Parallelogram.cpp
   )

add_library(librendering ${rendering_source})

target_include_directories(librendering
                           PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDE_DIR})
set_target_properties(librendering PROPERTIES OUTPUT_NAME rendering)


# build executable
set(main_source main.cpp)
add_executable(rendering ${main_source})


# linking
add_dependencies(rendering librendering)
target_link_libraries(rendering librendering)
