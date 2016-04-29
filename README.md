# MMGL: Mini Multithread Graphics Library

Mini Multithread Graphics Libaray (MMGL) is a library for displaying computer graphics. The library is able to render a variety of graphics objects including spheres, triangles, and more complex triangle meshes. The library is designed to be lightweight and easy-to-use, providing highly abstracted interfaces for beginners. It also employs parallel processing so that the rendering is highly efficient. The code is implemented with 100% portable C++11, so this cross-platform library works flawlessly on a variety of systems. Applications of this library include computer graphics, animation, and education for novice graphics programmers.

The library is comprised of a ray tracer, a multithreading framework, and many other supporting components. The ray tracer acts as the rendering engine, and the multithreading framework accelerates the rendering process using multicore processors. The library is written from scratch, without any dependencies on other libraries. The render results can be output as a picture file in bmp format, or be passed to calling applications using a provided handle.

This library is a course project for the *COMS W4995 Language Libary Design in C++* class in Spring 2016.

## Installation

The library sources can be cloned from <https://github.com/doomdagger/raytracer.git> using git. After downloading the source files, the library can be built and installed by simply running the `INSTALL.sh` script (on *nix systems). Similar commands can be run on other systems to compile and intall the library. The installation process uses tools such as cmake and make.

## Library Usage

The library can used easily by including the `mmgl` header and using the `mmgl` namespace. The following example code shows how the library can be integrated in another application:

```c++
#include <cmath>
#include <string>

#include "mmgl/mmgl.h"

using namespace mmgl;

int main(int argc, char* argv[]) {
    constexpr double PI {3.14159265};

    Scene scene;
    if (argc == 2) {
    	scene.config().thread_num(std::stoi(argv[1]));
    }
    scene.config().pixel_sampling_num(2)
                  .render_flag(Render::BVH);

    scene.camera().at(0, 0, 0)
                  .facing(0, 0, 1)
                  .focal_length(50)
                  .view_range(50, 50)
                  .image_size(1000, 1000);

    scene.pointLight().at(0, 0, -50).in(1, 1, 0);
    scene.ambientLight().in(0.05, 0.05, 0.05);

    auto& sphere = scene.sphere().radius(3);
    for (int i = 0; i < 8; ++i) {
        sphere.at(20 * std::sin(i*PI/4), 20 * std::cos(i*PI/4), 50);
        scene.render();
        scene.save(std::string("sphere") + std::to_string(i) + ".bmp");
    }

    return 0;
}
```

To compile this program, just compile with the C++11 flag and link with the MMGL library installed: `g++ -std=c++11 -O3 main.cpp -lmmgl -pthread`. Besides adding objects dynamically like this, the library also supports simplified wavefront .obj file format that describes a triangle mesh for complex scene design. Run the program and you'll see amazing graphics!
