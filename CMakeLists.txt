cmake_minimum_required(VERSION 3.27)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracer main.cpp
        ray_tracer_classes.h
        ray_tracer_classes.h
        scene_importer.h
        ray_trace.h
        ray_trace.cpp
        ray_tracer_classes.cpp
        file_output.h
        file_output.cpp)
