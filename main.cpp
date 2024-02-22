#include <iostream>
#include <cmath>
#include "ray_trace.h"
#include "scene_importer.h"



#define DEFAULT_WIDTH 512;
#define DEFAULT_HEIGHT 512;
#define DEFAULT_MAX_COLOR 255;

camera myCamera;
scene sceneInfo;

int width;
int height;

double DegreesToRadians(double);
void CalculateWindowSize(int[], const int[], float, float);
void CalculateWindowViewportRatio(const int[], const int[], double[]);

using namespace std;
int main()
{
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;

    //import the scene pls
    ImportScene(myCamera, sceneInfo);
    cout << "Scene Imported!!" << endl;

    //Here calculate everything we need so we can create the screen array
    int numPixels = width * height;
    int viewportSize[2] = {width, height};
    int windowSize[2] = {0,0};
    CalculateWindowSize(windowSize, viewportSize, myCamera.focal_length, myCamera.fov);
    double windowViewportSizeRatio[2] = {0.0, 0.0};
    CalculateWindowViewportRatio(windowSize, viewportSize, windowViewportSizeRatio);
    float halfWindowSize[2] = {(float)windowSize[0] / 2, (float)windowSize[1] / 2};





    cout << "Hello, World!" << endl;
    return 0;
}

//this function is for calculating a window size array given camera properties
void CalculateWindowSize(int windowSize[2], const int viewportSize[2], float focalLength, float fov)
{
    double fovDivided = fov / 2.0;
    double degToRad = DegreesToRadians(fovDivided);
    double x = focalLength * tan(degToRad) * 2;
    double y = x * viewportSize[1]/viewportSize[0];
    //now stick the window sizes back into the window size array
    windowSize[0] = (int)x;
    windowSize[1] = (int)y;
}

double DegreesToRadians(double degreeNumber)
{
    return degreeNumber * (M_PI / 180.0);
}

void CalculateWindowViewportRatio(const int windowSize[2], const int viewportSize[2], double ratioArray[2])
{
    //just divide the window sizes by the viewport sizes to get this nasty ratio
    ratioArray[0] = (double)windowSize[0] / (double)viewportSize[0];
    ratioArray[1] = (double)windowSize[1] / (double)viewportSize[1];
}



