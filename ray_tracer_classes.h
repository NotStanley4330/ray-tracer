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

    vec3 multiplyVecs(vec3 other)
    {
        return{x * other.x, y * other.y, z * other.z};
    }

    //this functions serves to clip vec3 values to 0,1 for color output
    vec3 clip()
    {
        vec3 clippedVec = *this;
        if (x > 1.0)
        {
            clippedVec.x = 1.0;
        }
        else if (x < 0.0)
        {
            clippedVec.x = 0.0;
        }

        if (y > 1.0)
        {
            clippedVec.y = 1.0;
        }
        else if (y < 0.0)
        {
            clippedVec.y = 0.0;
        }

        if (z > 1.0)
        {
            clippedVec.z = 1.0;
        }
        else if (z < 0.0)
        {
            clippedVec.z = 0.0;
        }

        return clippedVec;
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
    float diffuseCoeff;
    float specularCoeff;
    float ambeintCoeff;
    vec3 diffuseColor;
    vec3 specularColor;
    float glossCoeff;
    sphere()
    {
        center = vec3(0.0,0.0,0.0);
        radius = 0.0;
        diffuseCoeff = 0.0;
        specularCoeff = 0.0;
        ambeintCoeff = 0.0;
        diffuseColor = vec3(0.0, 0.0, 0.0);
        specularColor = vec3(0.0, 0.0, 0.0);
        glossCoeff = 0.0;

    }

    vec3 getNormal(vec3 point)
    {
        vec3 diffPoints = SubtractVec3(point, center);
        return diffPoints.normalized();
    }

    vec3 collideRay(vec3 rayOrigin, vec3 rayDirection, bool &isCollided)
    {
        vec3 distance = SubtractVec3(center, rayOrigin);
        float distSqr = distance.dot(distance);
        float distMag = sqrtf(distSqr);

        bool outside = (distMag >= radius);

        //need the dot product of the ray direction and the distance
        double closestApproach = (double)rayDirection.dot(distance);

        if(closestApproach < 0 && outside)
        {
            isCollided = false;
            return {0.0,0.0,0.0};
        }

        double closestApproachDistSurfaceSqr = pow((double)radius, (double)2) - (double)distSqr +
                                              pow(closestApproach, 2);

        if (closestApproachDistSurfaceSqr < 0)
        {
            isCollided = false;
            return {0.0,0.0,0.0};
        }

        double closestApproachDistSurface = sqrt(closestApproachDistSurfaceSqr);

        double t;
        if (outside)
        {
            t = closestApproach - closestApproachDistSurface;
        }
        else
        {
            t = closestApproach + closestApproachDistSurface;
        }

        //set isCollided to true and return the collidedPosition
        isCollided = true;
        return rayOrigin.add(rayDirection.multiplyScalar((float)t));



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
    int numSpheres;

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
};

class RayCollision
{
public:
    sphere collidedSphere;
    vec3 rayOrigin;
    vec3 pos; //position of the collision
    float distance; // the distance between the ray origin and this collision
    bool hasCollision;//A bool to check if there is an actual collision associated

    RayCollision(sphere inSphere, vec3 rayOrignIn, vec3 collidePos)
    {
        collidedSphere = inSphere;
        rayOrigin = rayOrignIn;
        pos = collidePos;
        vec3 difPosOrigin = SubtractVec3(pos, rayOrigin);
        distance = difPosOrigin.magnitude();
        hasCollision = true;
    }

    RayCollision()
    {
        distance = 100000;
        hasCollision = false;
    }
};

class Ray
{
public:
    vec3 origin;
    vec3 direction;

    Ray(vec3 originIn, vec3 directionIn)
    {
        origin = originIn;
        direction = directionIn;
    }

    RayCollision castRay(scene sceneInfo)
    {
        RayCollision closestCollide;
        for (int x = 0; x < sceneInfo.numSpheres; x++)
        {
            //create a bool to check if we really collide with the sphere and do the collision detection
            bool collided = false;
            vec3 collisionPos = sceneInfo.sphereList[x].collideRay(origin, direction, collided);
            if(collided)
            {
                RayCollision collision(sceneInfo.sphereList[x],origin,collisionPos);

                //if there is no initial collision or if the distance to this collision is closer, set this collision
                //as the closest one
                if (!closestCollide.hasCollision || collision.distance < closestCollide.distance)
                {
                    closestCollide = collision;
                }
            }
        }

        return closestCollide;
    }

};

#endif //RAY_TRACER_RAY_TRACER_CLASSES_H
