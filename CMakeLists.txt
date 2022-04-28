cmake_minimum_required(VERSION 3.21)
project(parallel_quickhull)

set(CMAKE_CXX_STANDARD 14)

add_executable(parallel_quickhull point.cpp parallel_prefix_sum.cpp seq_quickhull.cpp parallel_quickhull.cpp main.cpp)
#add_executable(parallel_quickhull point.cpp generate_points.cpp)
