cmake_minimum_required(VERSION 3.3)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

include_directories("/usr/local/include/OpenEXR")

set(SOURCE_FILES main.cc scene.cc surface.cc bbox.cc bvh_node.cc material.cc ray.cc common.cc point.cc vector.cc triangle.cc sphere.cc plane.cc intersection.cc intersection.h light.cc light.h ambientlight.cc ambientlight.h arealight.cc arealight.h pointlight.cc pointlight.h camera.cc camera.h scene_config.cc scene_config.h)
add_executable(raytracer ${SOURCE_FILES})
target_link_libraries(raytracer IlmImf Imath Half pthread)