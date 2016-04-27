cmake_minimum_required(VERSION 2.6)
project(mmgl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

# ---[ Includes
set(mmgl_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
include_directories(${mmgl_INCLUDE_DIR})
include_directories("/usr/local/include/OpenEXR")

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE hdrs ${PROJECT_SOURCE_DIR}/include/*.h)

add_library(mmgl SHARED ${srcs} ${hdrs})

# ---[ Install
install(DIRECTORY ${mmgl_INCLUDE_DIR} DESTINATION include/mmgl)
install(TARGETS mmgl EXPORT mmgl DESTINATION lib)