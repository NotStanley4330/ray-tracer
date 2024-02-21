//
// Created by starw on 2/21/2024.
//

#ifndef RAY_TRACER_RAY_TRACER_CLASSES_H
#define RAY_TRACER_RAY_TRACER_CLASSES_H


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
};

struct camera
{
    vec3 lookAt;
    vec3 lookFrom;
    vec3 lookUp;
    float fov;

    camera()
    {
        lookAt = vec3(0.0,0.0,0.0);
        lookFrom = vec3(0.0, 0.0, 0.0);
        lookUp = vec3(0.0,0.0,0.0);
        fov = 90.0;
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
