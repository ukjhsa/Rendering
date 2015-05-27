# Rendering

### Description

Raytracing exercise includes distributed ray tracing and Phong lighting:

- Distributed ray tracing
  - Monte Carlo method.
  - sampled reflected ray.
  - sampled light.
- Phong lighting
  - ambient.
  - diffuse.
  - specular

It contains:

- Three models
  - Sphere.
  - Triangle.
  - Parallelogram.
- Supported output image
  - ppm (The portable pixmap format.)

### Requirement:
1. CMake 2.8.12 or the newer.
2. C++ compiler with c++11 supported.

### Build and Run

For Windows users, use the _MinGW_ to build:

```{.sh}
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

For Unix users:

```{.sh}
mkdir build
cd build
cmake ..
make
```

Then, execute the rendering along with the model.txt file at the same path.

### Reference

[http://en.wikipedia.org/wiki/Ray_tracing_(graphics)](http://en.wikipedia.org/wiki/Ray_tracing_(graphics))
[http://en.wikipedia.org/wiki/Distributed_ray_tracing](http://en.wikipedia.org/wiki/Distributed_ray_tracing)
[http://en.wikipedia.org/wiki/Phong_reflection_model](http://en.wikipedia.org/wiki/Phong_reflection_model)
