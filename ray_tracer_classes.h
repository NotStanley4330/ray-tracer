//
// Created by starw on 2/21/2024.
//

#ifndef RAY_TRACER_RAY_TRACER_CLASSES_H
#define RAY_TRACER_RAY_TRACER_CLASSES_H
#include <cmath>

class vec3
{
public:
    float x;
    float y;
    float z;

    //Create a vec3 with empty values
    vec3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    //create a vec 3 with values
    vec3(float xIn, float yIn, float zIn)
    {
        x = xIn;
        y = yIn;
        z = zIn;
    }

    //this function simply returns the dot product of this vector with another one
    float dot(vec3 other)
    {
        return (float)((x * other.x) + (y * other.y) + (z * other.z));
    }

    //returns the scalar length of the vector
    float magnitude()
    {
        vec3 copy = *this;
        return sqrtf(dot(copy));
    }

    //returns a version of this vector with each element divided by a floating point value
    vec3 divide(float divisor)
    {
        return {(x / divisor), (y / divisor), (z / divisor)};
    }

    //returns a new vector pointing in the same direction but with length 1
    vec3 normalized()
    {
        float mag = magnitude();
        if (mag != 0)
        {
            return divide(mag);
        }
        else
        {
            return *this;
        }
    }

    //returns a cross product of this vector with another one
    vec3 cross(vec3 other)
    {
        //first, we need to do (this.y * other.z) - (this.z * other.y)
        float xResult = (y * other.z) - (other.y * z);
        //next, we need to do (this.x * other.z) - (this.z * other.x)
        float yResult = (x * other.z) - (z * other.x);
        //last, we need to do (this.x * other.y) - (this.y * other.x)
        float zResult = (x * other.y) - (y * other.x);
        return {xResult, yResult, zResult};
    }

    vec3 multiplyScalar(float scalar)
    {
        return {x * scalar, y * scalar, z *scalar};
    }

    //adds a second vec3 and outputs the sum vec3
    vec3 add(vec3 other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }
};

vec3 SubtractVec3(vec3 first, vec3 second);

struct camera
{


    vec3 pos;
    vec3 relLookAt;
    float focal_length;
    float fov;
    vec3 forward;
    vec3 up;
    vec3 right;


    camera()
    {
        vec3 lookAt = vec3(0.0,0.0,0.0);
        vec3 lookFrom = vec3(0.0, 0.0, 1.0);
        vec3 lookUp = vec3(0.0,1.0,0.0);


        fov = 90;
        pos = lookFrom;
        relLookAt = SubtractVec3(lookAt, lookFrom);

        //focal length is just the square root of the dot product of the relLookAt vector
        focal_length = relLookAt.magnitude();

        //forward is the normalized form of rel look at
        forward = relLookAt.normalized();
        up = lookUp;

        //right vector is the cross product of the forward and up vectors
        right = forward.cross(up);





    }

    camera(vec3 lookAtIn, vec3 lookFromIn, vec3 lookUpIn, float fovIn)
    {
        fov = fovIn;
        //set pos as lookFrom
        pos = lookFromIn;
        relLookAt = SubtractVec3(lookAtIn, pos);

        //focal length = sqrt(magnitude(relLookAt))
        focal_length = relLookAt.magnitude();

        //forward is the normalized form of rel look at
        forward = relLookAt.normalized();
        up = lookUpIn;

        //right vector is the cross product of forward and up
        right = forward.cross(up);

    }
};

class sphere
{
public:
    vec3 center;
    float radius;
    float Kd;
    float Ks;
    float Ka;
    vec3 Od;
    vec3 Os;
    float Kgls;
    sphere()
    {
        center = vec3(0.0,0.0,0.0);
        radius = 0.0;
        Kd = 0.0;
        Ks = 0.0;
        Ka = 0.0;
        Od = vec3(0.0,0.0,0.0);
        Os = vec3(0.0,0.0,0.0);
        Kgls = 0.0;

    }


};

class scene
{
public:
    vec3 directionToLight;
    vec3 lightColor;
    vec3 ambientLight;
    vec3 backgroundColor;
    sphere sphereList[10];

    scene()
    {
        numSpheres = 0;
        directionToLight = vec3(0.0,0.0,0.0);
        lightColor = vec3(0.0,0.0,0.0);
        ambientLight = vec3(0.0,0.0,0.0);
        backgroundColor = vec3(0.0,0.0,0.0);
    }

    void addSphere(sphere inputSphere)
    {
        //set the sphere to given info and increment the number of spheres
        sphereList[numSpheres] = inputSphere;
        numSpheres++;
    }

private:
    int numSpheres;



};

#endif //RAY_TRACER_RAY_TRACER_CLASSES_H
