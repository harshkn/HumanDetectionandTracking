cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
 
project(detect_humans)
 
find_package(OpenCV REQUIRED)
 
add_executable(detect_humans detect_humans.cpp)
 
target_link_libraries (detect_humans  ${OpenCV_LIBS})
