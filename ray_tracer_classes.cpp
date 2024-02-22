//
// Created by starw on 2/21/2024.
//
#include "ray_tracer_classes.h"


//this function exists to subtract the elements of vec3s from one another
//The second vec3 will be subtracted from the first
vec3 SubtractVec3(vec3 first, vec3 second)
{
    vec3 result;
    result.x = first.x - second.x;
    result.y = first.y - second.y;
    result.z = first.z - second.z;

    return result;
}