//
// Created by starw on 2/21/2024.
//

#include "ray_trace.h"
#include <iostream>
#include <random>
#include <cmath>

camera sceneCamera;
scene myScene;
using namespace std;
void rayTraceAll(vec3** imageData, camera inputCamera, scene inputScene, int width, int height,
                   double windowViewportRatio[], float halfWindowSize[])
{
    //import camera and scene
    sceneCamera = inputCamera;
    myScene = inputScene;



    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            //TEST CODE TO MAKE SURE I AM EDITING THE STUPID ARRAY PROPERLY
//            imageData[x][y].x = 1.0 * (float)y;
//            imageData[x][y].y = 0.9 * (float)y;
//            imageData[x][y].z = 0.8 * (float)y;

            //ray trace this pixel
            imageData[x][y] = rayTracePixel(x,y, windowViewportRatio, halfWindowSize);
        }
    }
}

//function retrieves the color for a single picture of the image
vec3 rayTracePixel(int x, int y, double winViewRatio[], float halfWinSize[])
{
    //first lets set an array as the point on the screen
    int viewPoint[2] = {x,y};
    //convert that point to a window point
    float windowPoint[2] = {0.0, 0.0};
    viewportToWindow(windowPoint, viewPoint, winViewRatio, halfWinSize);
    //need a 3d point for 3d space
    vec3 windowPointVec(windowPoint[0], (windowPoint[1]* -1), 0.0);
    vec3 relWorldPoint = windowToRelWorld(windowPointVec);
    //cout << "transforms done!" << endl;
    //for now lets just assign random pixel values so that we can make sure the file works
    //send out the rays!
    return getColor(sceneCamera.pos, relWorldPoint.normalized());

    return {0.0,0.0,0.0};
}


//this is the function that actually sends out the ray and returns the vec3 color value
vec3 getColor(vec3 origin, vec3 direction)
{
    Ray pixelRay(origin, direction);
    RayCollision collision = pixelRay.castRay(myScene);

    //shade the pixel with the sphere if we have a sphere collision
    if (collision.hasCollision)
    {
//        cout << "Ray at " << origin.x << ", " << origin.y << ", " << origin.z << endl;
//        cout << "Collided with sphere at: " << collision.collidedSphere.center.x << ", " << collision.collidedSphere.center.y;
//        cout << ", " << collision.collidedSphere.center.z << endl;
        vec3 viewDir = direction.multiplyScalar(-1.0);
        return shade(collision.collidedSphere, collision.pos, viewDir);

    }
    return myScene.backgroundColor;
}

//transpform the viewport coords to window ones
void viewportToWindow(float windowPoint[], const int viewPoint[], const double winViewRatio[], const float halfWinSize[])
{
    windowPoint[0] = float(((double)viewPoint[0] * winViewRatio[0]) - halfWinSize[0]);
    windowPoint[1] = float(((double)viewPoint[1] * winViewRatio[1]) - halfWinSize[1]);
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
vec3 shade(sphere mySphere, vec3 position, vec3 viewDir)
{
    //get surface normal
    vec3 surfaceNormal = mySphere.getNormal(position);
    float normalDotLight = surfaceNormal.dot(myScene.directionToLight);
    //This equation should be 2 * surfaceNormal * normalDotLight - directionToLight
    vec3 lightReflectionDirection = SubtractVec3(surfaceNormal.multiplyScalar(2).multiplyScalar(normalDotLight),
                                                 myScene.directionToLight);
    //viewdir dot lightReflectionDirection
    float viewDotLight = viewDir.dot(lightReflectionDirection);

    //ambient lighting
    vec3 ambient = myScene.ambientLight.multiplyVecs(mySphere.diffuseColor);
    ambient = ambient.multiplyScalar(mySphere.ambeintCoeff);

    //Diffuse lighting
    //equation is lightColor * obj.diffuseColor * max of 0 and normalDotLight
    vec3 diffuse = myScene.lightColor.multiplyVecs(mySphere.diffuseColor)
            .multiplyScalar(max((float)0.0, normalDotLight));
    diffuse = diffuse.multiplyScalar(mySphere.diffuseCoeff);

    //Specular lighting
    //This equation is lightColor * obj.specularColor * (max of 0.0, and viewDotLight)^obj.glossCoeff
    vec3 specular = myScene.lightColor.multiplyVecs(mySphere.specularColor)
            .multiplyScalar(pow(max((float)0.0, viewDotLight),mySphere.glossCoeff));
    specular = specular.multiplyScalar(mySphere.specularCoeff);

    //color = ambient + diffuse + specular
    vec3 color = ambient.add(diffuse).add(specular);

    //clip the dang values
    vec3 colorClipped = color.clip();

    return colorClipped;



}