# raytracer
high-efficient ray tracer written in c++

### How to build it

Please following the commands below:
```bash
# this is a comment

# clone our project
$ git clone https://github.com/doomdagger/raytracer.git

# change directory to root folder of our project
$ cd raytracer

# create a folder named build
$ mkdir build

# change directory to build folder
$ cd build

$ execute cmake, attention: two points here
$ cmake ..

# execute make
$ make

# install project, default installation path is /usr/local/include and /usr/local/lib
$ sudo make install
```

### How to use it

Create a project with a `CMakeLists.txt` file containing the following content:
```cmake
cmake_minimum_required(VERSION 2.6)
project(prog_out)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/local/include/mmgl")

set(SOURCE_FILES main.cpp)
add_executable(prog_out ${SOURCE_FILES})
target_link_libraries(prog_out /usr/local/lib/libmmgl.so pthread)
```

The content of `main.cpp`:
```c++
#include <iostream>
#include "mmgl/mmgl.h"

using namespace std;
using namespace mmgl;

int main() {
    Scene scene;

    scene.config.pixel_sampling_num(2);
    scene.config.render_flag(Render::BVH);

    Sphere &sphere = scene.sphere().at(0, 13.67f, -62.57f).radius(10);

    scene.pointLight(-80, 120, -46.6f, 1, 1, 1);
    scene.ambientLight(0.05, 0.05, 0.05);

    scene.configCamera(24.2, 29.3, 53.6, 0, 0, -1, 35, 35, 35, 1000, 1000);

    scene.render();

    scene.save("/home/lihe/Desktop/test.bmp");

    sphere.at(20, 13.67f, -62.57f);

    scene.render();

    scene.save("/home/lihe/Desktop/test1.bmp");

//    Scene scene("/home/lihe/Desktop/parser/teapot.txt");
//
//    scene.config.shadow_sampling_num(1);
//    scene.config.pixel_sampling_num(1);
//    scene.config.recursive_limit(2);
//    scene.config.render_flag(Render::BVH);
//
//    scene.render();
//
//    scene.save("/home/lihe/Desktop/test.bmp");

    return 0;
}
```
