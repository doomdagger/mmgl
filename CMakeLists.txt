cmake_minimum_required(VERSION 3.3)
project(raytracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc scene.cc surface.cc bbox.cc bvh_node.cc material.cc ray.cc common.cc point.cc vector.cc triangle.cc sphere.cc plane.cc intersection.cc intersection.h)
add_executable(raytracer ${SOURCE_FILES})