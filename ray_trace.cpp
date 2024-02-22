//
// Created by starw on 2/21/2024.
//

#include "ray_trace.h"
#include <iostream>
#include <random>

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
    cout << "transforms done!" << endl;
    //for now lets just assign random pixel values so that we can make sure the file works
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<float> dist(0.0f, 1.0f);
//    float randFloat = dist(gen);
//    float randFloat2 = dist(gen);
//    float randFloat3 = dist(gen);
//
//    //don't ever do this
//    return {randFloat,randFloat2,randFloat3};

    return {0.0,0.0,0.0};
}

void viewportToWindow(float windowPoint[], int viewPoint[], double winViewRatio[], float halfWinSize[])
{
    //TODO: remove this debug code eventually
//    cout << "Window point: " << windowPoint[0] << ", " << windowPoint[1] << endl;
//    cout << "View point: " << viewPoint[0] << ", " << viewPoint[1] << endl;
//    cout << "win view ratio: " << winViewRatio[0] << ", " << winViewRatio[1] << endl;
//    cout << "Half win size: " << halfWinSize[0] << ", " << halfWinSize[1] << endl;
    windowPoint[0] = float(((double)viewPoint[0] * winViewRatio[0]) - halfWinSize[0]);
    windowPoint[1] = float(((double)viewPoint[1] * winViewRatio[1]) - halfWinSize[1]);


    //cout << "I wanna make sure this works" << endl;
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