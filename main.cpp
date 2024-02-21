#include <iostream>
#include "ray_tracer_classes.h"
#include "scene_importer.h"



#define DEFAULT_WIDTH = 512;
#define DEFAULT_HEIGHT = 512;
#define DEFAULT_MAX_COLOR = 255;

camera myCamera;
scene sceneInfo;

using namespace std;
int main()
{
    ImportScene(myCamera, sceneInfo);






    cout << "Hello, World!" << endl;
    return 0;
}

