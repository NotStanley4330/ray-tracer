//
// Created by starw on 2/21/2024.
//
#include "ray_tracer_classes.h"


#ifndef RAY_TRACER_RAY_TRACE_H
#define RAY_TRACER_RAY_TRACE_H

void rayTraceAll(vec3**, camera, scene, int, int, double [], float[]);

vec3 rayTracePixel(int, int, double[], float[]);

void viewportToWindow(float[], const int [], const double[], const float[]);

vec3 windowToRelWorld(vec3);

vec3 getColor(vec3, vec3);
vec3 shade(sphere, vec3, vec3);


#endif //RAY_TRACER_RAY_TRACE_H
