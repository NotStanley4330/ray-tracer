//
// Created by starw on 2/21/2024.
//

#include "ray_trace.h"
#include <iostream>
#include <random>
#include <cmath>

#define FADE_LIMIT 0.01

camera sceneCamera;
scene myScene;
using namespace std;
void rayTraceAll(vec3** imageData, camera inputCamera, scene inputScene, int width, int height,
                   double windowViewportRatio[], double halfWindowSize[])
{
    //import camera and scene
    sceneCamera = inputCamera;
    myScene = inputScene;



    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            //ray trace this pixel
            imageData[x][y] = rayTracePixel(x,y, windowViewportRatio, halfWindowSize);
        }
    }
}

//function retrieves the color for a single picture of the image
vec3 rayTracePixel(int x, int y, double winViewRatio[], double halfWinSize[])
{
    //first lets set an array as the point on the screen
    int viewPoint[2] = {x,y};
    //convert that point to a window point
    double windowPoint[2] = {0.0, 0.0};
    viewportToWindow(windowPoint, viewPoint, winViewRatio, halfWinSize);
    //need a 3d point for 3d space
    vec3 windowPointVec(windowPoint[0], (windowPoint[1]* -1), 0.0);
    vec3 relWorldPoint = windowToRelWorld(windowPointVec);
    //cout << "transforms done!" << endl;
    //for now lets just assign random pixel values so that we can make sure the file works
    //send out the rays!
    return getColor(sceneCamera.pos, relWorldPoint.normalized(), 1.0, 0);

    return {0.0,0.0,0.0};
}


//this is the function that actually sends out the ray and returns the vec3 color value
vec3 getColor(vec3 origin, vec3 direction, double fade, int reflections)
{
    if (fade <= FADE_LIMIT || reflections > 10)
    {
        return {0.0, 0.0, 0.0};
    }



    Ray pixelRay(origin, direction);
    RayCollision collision = pixelRay.castRay(myScene);

    //shade the pixel with the sphere if we have a sphere collision
    if (collision.hasCollision)
    {
//        cout << "Ray at " << origin.x << ", " << origin.y << ", " << origin.z << endl;
//        cout << "Collided with sphere at: " << collision.collidedSphere.center.x << ", " << collision.collidedSphere.center.y;
//        cout << ", " << collision.collidedSphere.center.z << endl;
        vec3 viewDir = direction.multiplyScalar(-1.0);
        vec3 objNormal = collision.collidedSphere->getNormal(collision.pos);
        //lets offset this collision so we dont get trapped inside an object.
        //position += 0.01 * normal
        collision.pos = collision.pos.add(objNormal.multiplyScalar(0.01));

        bool inShadow = isInShadow(collision.pos);
        //ReflectionDirection = ray direction + ( -2 *normal * dot(pixelRay.direction, normal))
        vec3 reflectionDirection = pixelRay.direction.add(objNormal.multiplyScalar(
                pixelRay.direction.dot(objNormal) * - 2.0f));

        //collision.pos + 0.01 * reflectionDirection
        vec3 offsetOrigin = collision.pos.add(reflectionDirection.multiplyScalar(0.01f));

        vec3 reflectedColor = getColor(offsetOrigin, reflectionDirection,
                                       fade * collision.collidedSphere->getReflectivity(), reflections + 1);

        return shade(collision.collidedSphere, collision.pos, viewDir, inShadow, reflectedColor);

    }
    return myScene.backgroundColor;
}

//This function casts a ray towards the light source to determine if the point is in shadow
bool isInShadow(vec3 point)
{
    Ray shadowRay(point, myScene.directionToLight);
    //Offset the ray slightly so that we don't just collide with our object
    //Math should be origin += 0.01 * direction
    shadowRay.origin = shadowRay.origin.add(shadowRay.direction.multiplyScalar(0.01));
    RayCollision collision = shadowRay.castRay(myScene);

    //return if it has collided with something
    return collision.hasCollision;
}

//transform the viewport coords to window ones
void viewportToWindow(double windowPoint[], const int viewPoint[], const double winViewRatio[], const double halfWinSize[])
{
    windowPoint[0] = ((viewPoint[0] * winViewRatio[0]) - halfWinSize[0]);
    windowPoint[1] = ((viewPoint[1] * winViewRatio[1]) - halfWinSize[1]);
}

//this function transforms the window point to a relative world point
vec3 windowToRelWorld(vec3 windowPointVec)
{
    //do camera.relLookAt + windowPointVec[0]*camera.right + windowPointVec[1] * camera.up +
    // windowPointVec[2] * camera.forward
    vec3 relWorld(sceneCamera.relLookAt);
    vec3 temp1 = sceneCamera.right.multiplyScalar(windowPointVec.x);
    vec3 temp2 = sceneCamera.up.multiplyScalar(windowPointVec.y);
    vec3 temp3 = sceneCamera.forward.multiplyScalar(windowPointVec.z);
    relWorld = relWorld.add(temp1);
    relWorld = relWorld.add(temp2);
    relWorld = relWorld.add(temp3);
    return relWorld;
}

//this function applies the phong shading
vec3 shade(object* myObject, vec3 position, vec3 viewDir, bool inShadow, vec3 reflectedColor)
{


    double shadowCoefficient;
    if (inShadow)
    {
        shadowCoefficient = 0;
    }
    else
    {
        shadowCoefficient = 1;
    }

    //get surface normal
    vec3 surfaceNormal = myObject->getNormal(position);
    double normalDotLight = surfaceNormal.dot(myScene.directionToLight);
    //This equation should be 2 * surfaceNormal * normalDotLight - directionToLight
    vec3 lightReflectionDirection = SubtractVec3(surfaceNormal.multiplyScalar(2).multiplyScalar(normalDotLight),
                                                 myScene.directionToLight);
    //viewdir dot lightReflectionDirection
    double viewDotLight = viewDir.dot(lightReflectionDirection);

    //Ambient lighting
    //printf("Diffuse color: %f, %f, %f\n", myObject->getDiffuseColor().x, myObject->getDiffuseColor().y, myObject->getDiffuseColor().z);

    vec3 ambient = myScene.ambientLight.multiplyVecs(myObject->getDiffuseColor());
    ambient = ambient.multiplyScalar(myObject->getAmbeintCoeff());

    //Diffuse lighting
    //equation is lightColor * obj.diffuseColor * max of 0 and normalDotLight
    vec3 diffuse = myScene.lightColor.multiplyVecs(myObject->getDiffuseColor())
            .multiplyScalar(max(0.0, normalDotLight));
    diffuse = diffuse.multiplyScalar(myObject->getDiffuseCoeff());
    diffuse = diffuse.multiplyScalar(shadowCoefficient);

    //Specular lighting
    //This equation is lightColor * obj.specularColor * (max of 0.0, and viewDotLight)^obj.glossCoeff
    vec3 specular = myScene.lightColor.multiplyVecs(myObject->getSpecularColor())
            .multiplyScalar(pow(max(0.0, viewDotLight), myObject->getGlossCoeff()));
    specular = specular.multiplyScalar(myObject->getSpecularCoeff());
    specular = specular.multiplyScalar(shadowCoefficient);

    //REFLECTIONS
    vec3 reflectedObjColor = reflectedColor.multiplyScalar(myObject->getReflectivity());

    //color = ambient + diffuse + specular + reflected
    vec3 color = ambient.add(diffuse).add(specular).add(reflectedObjColor);

    //clip the dang values
    vec3 colorClipped = color.clip();

    return colorClipped;



}