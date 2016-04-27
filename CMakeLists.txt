cmake_minimum_required(VERSION 2.6)
project(mmgl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

# ---[ Includes
set(mmgl_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${mmgl_INCLUDE_DIR} ${PROJECT_BINARY_DIR})
#include_directories("/usr/local/include")
#include_directories("/usr/include")
#include_directories(include)

SET(srcs
        src/core/camera.cc
        src/core/scene.cc
        src/light/ambientlight.cc
        src/light/arealight.cc
        src/light/pointlight.cc
        src/light/light.cc
        src/surface/bbox.cc
        src/surface/bvh_node.cc
        src/surface/intersection.cc
        src/surface/material.cc
        src/surface/ray.cc
        src/surface/sphere.cc
        src/surface/surface.cc
        src/surface/triangle.cc
        src/util/common.cc
        src/util/point.cc
        src/util/scene_config.cc
        src/util/vector.cc
        )

SET(hdrs
        include/core/camera.h
        include/core/scene.h
        include/light/ambientlight.h
        include/light/arealight.h
        include/light/pointlight.h
        include/light/light.h
        include/surface/bbox.h
        include/surface/bvh_node.h
        include/surface/intersection.h
        include/surface/material.h
        include/surface/ray.h
        include/surface/sphere.h
        include/surface/surface.h
        include/surface/triangle.h
        include/util/common.h
        include/util/point.h
        include/util/scene_config.h
        include/util/vector.h
        )

add_library(mmgl SHARED ${srcs} ${hdrs})
target_link_libraries(mmgl IlmImf Imath Half pthread)

# ---[ Install
install(DIRECTORY ${mmgl_INCLUDE_DIR} DESTINATION include)