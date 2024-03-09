//
// Created by starw on 2/21/2024.
//

#ifndef RAY_TRACER_RAY_TRACER_CLASSES_H
#define RAY_TRACER_RAY_TRACER_CLASSES_H
#include <cmath>

class vec3
{
public:
    double x;
    double y;
    double z;

    //Create a vec3 with empty values
    vec3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    //create a vec 3 with values
    vec3(double xIn, double yIn, double zIn)
    {
        x = xIn;
        y = yIn;
        z = zIn;
    }

    //this function simply returns the dot product of this vector with another one
    double dot(vec3 other)
    {
        return ((x * other.x) + (y * other.y) + (z * other.z));
    }

    //returns the scalar length of the vector
    double magnitude()
    {
        vec3 copy = *this;
        return sqrt(dot(copy));
    }

    //returns a version of this vector with each element divided by a floating point value
    vec3 divide(double divisor)
    {
        return {(x / divisor), (y / divisor), (z / divisor)};
    }

    //returns a new vector pointing in the same direction but with length 1
    vec3 normalized()
    {
        double mag = magnitude();
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
        double xResult = (y * other.z) - (other.y * z);
        //next, we need to do (this.x * other.z) - (this.z * other.x)
        double yResult = (x * other.z) - (z * other.x);
        //last, we need to do (this.x * other.y) - (this.y * other.x)
        double zResult = (x * other.y) - (y * other.x);
        return {xResult, yResult, zResult};
    }

    vec3 multiplyScalar(double scalar)
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
    double focal_length;
    double fov;
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

    camera(vec3 lookAtIn, vec3 lookFromIn, vec3 lookUpIn, double fovIn)
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


class object
{
public:
    double diffuseCoeff;
    double specularCoeff;
    double ambeintCoeff;
    vec3 diffuseColor;
    vec3 specularColor;
    double glossCoeff;
    double reflectivity;

    virtual vec3 getNormal(vec3 point)
    {
        return {0.0,0.0,0.0};
    }
    virtual vec3 collideRay(vec3 rayOrigin, vec3 rayDirection, bool &isCollided)
    {
        isCollided = false;
        return {0.0,0.0,0.0};
    }

    virtual vec3 getDiffuseColor()
    {
        return  diffuseColor;
    }

    virtual vec3 getSpecularColor()
    {
        return specularColor;
    }
    virtual double getDiffuseCoeff()
    {
        return diffuseCoeff;
    }

    virtual double getSpecularCoeff()
    {
        return specularCoeff;
    }

    virtual double getAmbeintCoeff()
    {
        return ambeintCoeff;
    }

    virtual double getGlossCoeff()
    {
        return glossCoeff;
    }

    virtual double getReflectivity()
    {
        return reflectivity;
    }


};

class sphere : public object
{
public:
    vec3 center;
    double radius;
    double diffuseCoeff;
    double specularCoeff;
    double ambeintCoeff;
    vec3 diffuseColor;
    vec3 specularColor;
    double glossCoeff;
    double reflectivity;
    sphere()
    {
        this->center = vec3(0.0,0.0,0.0);
        this->radius = 0.0;
        this->diffuseCoeff = 0.0;
        this->specularCoeff = 0.0;
        this->ambeintCoeff = 0.0;
        this->diffuseColor = vec3(0.0, 0.0, 0.0);
        this->specularColor = vec3(0.0, 0.0, 0.0);
        this->glossCoeff = 0.0;
        this->reflectivity = 0.0;

    }

    sphere(vec3 centerIn, double radiusIn, double diffIn, double specIn, double ambIn, vec3 diffColorIn, vec3 specColorIn,
           double glossIn, double reflectIn)
    {
        this->center = centerIn;
        this->radius = radiusIn;
        this->diffuseCoeff = diffIn;
        this->specularCoeff = specIn;
        this->ambeintCoeff = ambIn;
        this->diffuseColor = diffColorIn;
        this->specularColor = specColorIn;
        this->glossCoeff = glossIn;
        this->reflectivity = reflectIn;
    }

    vec3 getNormal(vec3 point) override
    {
        vec3 diffPoints = SubtractVec3(point, center);
        return diffPoints.normalized();
    }

    vec3 getDiffuseColor() override
    {
        return this->diffuseColor;
    }

    vec3 getSpecularColor() override
    {
        return this->specularColor;
    }

    double getDiffuseCoeff() override
    {
        return this->diffuseCoeff;
    }

    double getSpecularCoeff() override
    {
        return this->specularCoeff;
    }

    double getAmbeintCoeff() override
    {
        return this->ambeintCoeff;
    }

    double getGlossCoeff() override
    {
        return this->glossCoeff;
    }

    double getReflectivity() override
    {
        return this->reflectivity;
    }

    vec3 collideRay(vec3 rayOrigin, vec3 rayDirection, bool &isCollided) override
    {
        vec3 distance = SubtractVec3(center, rayOrigin);
        double distSqr = distance.dot(distance);
        double distMag = sqrt(distSqr);

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
        return rayOrigin.add(rayDirection.multiplyScalar(t));
    }
};

class plane
{
public:
    vec3 normal;
    double distFromOrigin;

    plane()
    {
        normal = {0.0,0.0,0.0};
        distFromOrigin = -100000;
    }

    plane(vec3 inNormal, vec3 inPos)
    {
        normal = inNormal.normalized();
        distFromOrigin = normal.dot(inPos) * -1.0;
    }

    vec3 getNormal()
    {
        return normal;
    }

    vec3 collideRay(vec3 rayOrigin, vec3 rayDirection, bool &isCollided)
    {
        //see if it even collides or the plane is parallel to the ray
        double collide = normal.dot(rayDirection);

        if (collide == 0)
        {
            //Ray is parallel to plane
            isCollided = false;
            return {0.0,0.0,0.0};
        }

        //vO = *dot(normal, origin) + distFromOrigin) * -1
        double vO = (normal.dot(rayOrigin) + distFromOrigin) * -1.0;
        double t = vO / collide;

        if (t <= 0)
        {
            //Intersection is behind the screen
            isCollided = false;
            return {0.0,0.0,0.0};
        }

        //if we got this far there is a colliison in front of the camera
        isCollided = true;
        //return rayOrigin + rayDirection * t
        return rayOrigin.add(rayDirection.multiplyScalar(t));
    }
};

class triangle: public object
{
public:
    vec3 points[3];
    double diffuseCoeff;
    double specularCoeff;
    double ambeintCoeff;
    vec3 diffuseColor;
    vec3 specularColor;
    double glossCoeff;
    double reflectivity;
    plane polygonPlane;

    triangle()
    {
        points[0] = vec3(0.0,0.0,0.0);
        points[1] = vec3(0.0,1.0,0.0);
        points[2] = vec3(1.0,0.0,0.0);
        this->diffuseCoeff = 0.0;
        this->specularCoeff = 0.0;
        this->ambeintCoeff = 0.0;
        this->diffuseColor = vec3(0.0, 0.0, 0.0);
        this->specularColor = vec3(0.0, 0.0, 0.0);
        this->glossCoeff = 0.0;
        this->reflectivity = 0.0;
    }

    vec3 getNormal(vec3 point) override
    {
        //we need to get two vectors of two sides and then take their cross products
        vec3 vector1 = SubtractVec3(points[1],points[0]);
        vec3 vector2 = SubtractVec3(points[2],points[1]);

        vec3 normal = vector1.cross(vector2).normalized();
        return normal;
    }

    void setTrianglePlane()
    {
        polygonPlane = plane(this->getNormal({0.0,0.0,0.0}), points[0]);
    }

    vec3 getDiffuseColor() override
    {
        return this->diffuseColor;
    }

    vec3 getSpecularColor() override
    {
        return this->specularColor;
    }

    double getDiffuseCoeff() override
    {
        return this->diffuseCoeff;
    }

    double getSpecularCoeff() override
    {
        return this->specularCoeff;
    }

    double getAmbeintCoeff() override
    {
        return this->ambeintCoeff;
    }

    double getGlossCoeff() override
    {
        return this->glossCoeff;
    }

    double getReflectivity() override
    {
        return this->reflectivity;
    }

    vec3 collideRay(vec3 rayOrigin, vec3 rayDirection, bool &isCollided) override
    {
        vec3 planeCollision = polygonPlane.collideRay(rayOrigin, rayDirection, isCollided);
        if (!isCollided)
        {
            isCollided = false; //just to be sure
            return {0.0,0.0,0.0};
        }

        vec3 edge0 = (SubtractVec3(points[1],points[0]));
        vec3 edge1 = SubtractVec3(points[2], points[1]);
        vec3 edge2 = SubtractVec3(points[0], points[1]);

        vec3 c0 = SubtractVec3(planeCollision, points[0]);
        vec3 c1 = SubtractVec3(planeCollision, points[1]);
        vec3 c2 = SubtractVec3(planeCollision, points[2]);

        vec3 normal = getNormal({0.0,0.0,0.0});
        if (normal.dot(edge0.cross(c0)) > 0 &&normal.dot(edge1.cross(c1)) > 0 &&
        normal.dot(edge2.cross(c2)) > 0)
        {
            isCollided = true;
            return planeCollision;
        }

        isCollided = false;
        return {0.0,0.0,0.0};


    }
};

class scene
{
public:
    vec3 directionToLight;
    vec3 lightColor;
    vec3 ambientLight;
    vec3 backgroundColor;
    object* sphereList[20];
    int numObjects;


    scene()
    {
        numObjects = 0;
        directionToLight = vec3(0.0,0.0,0.0);
        lightColor = vec3(0.0,0.0,0.0);
        ambientLight = vec3(0.0,0.0,0.0);
        backgroundColor = vec3(0.0,0.0,0.0);
    }

    void addSphere(sphere inputSphere)
    {
        //set the sphere to given info and increment the number of spheres
        sphereList[numObjects] = new sphere(inputSphere);
        numObjects++;
    }

    void addPolygon(triangle inputPolygon)
    {
        sphereList[numObjects] = new triangle(inputPolygon);
        numObjects++;
    }
};

class RayCollision
{
public:
    object* collidedSphere;
    vec3 rayOrigin;
    vec3 pos; //position of the collision
    double distance; // the distance between the ray origin and this collision
    bool hasCollision;//A bool to check if there is an actual collision associated

    RayCollision(object* inSphere, vec3 rayOrignIn, vec3 collidePos)
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
        collidedSphere = new sphere();
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
        for (int x = 0; x < sceneInfo.numObjects; x++)
        {
            //create a bool to check if we really collide with the sphere and do the collision detection
            bool collided = false;
            vec3 collisionPos = sceneInfo.sphereList[x]->collideRay(origin, direction, collided);
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
