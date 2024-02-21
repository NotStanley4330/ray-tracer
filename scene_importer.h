//
// Created by starw on 2/21/2024.
//

#ifndef RAY_TRACER_SCENE_IMPORTER_H
#define RAY_TRACER_SCENE_IMPORTER_H
#include "ray_tracer_classes.h"
#include <string>
#include <fstream>

using namespace std;
void ImportScene(camera &myCamera, scene &sceneInfo)
{
    fstream fin;
    fin.open("C:\\Users\\starw\\CLionProjects\\ray_tracer\\scene2.txt", fstream::in);


    //start reading in input, these are just throw away variables
    string garbage, inOne, inTwo, inThree;


    //read in CameraLookAt
    fin >> garbage >> inOne >> inTwo >> inThree;
    vec3 lookAt(stof(inOne), stof(inTwo), stof(inThree));

    //read in CameraLookFrom
    fin>> garbage >> inOne >> inTwo >> inThree;
    vec3 lookFrom(stof(inOne), stof(inTwo), stof(inThree));

    //read in CameraLookUp
    fin>> garbage >> inOne >> inTwo >> inThree;
    vec3 lookUp(stof(inOne), stof(inTwo), stof(inThree));

    //read in FieldOfView
    fin>> garbage >> inOne;
    float fov = stof(inOne);

    myCamera = camera(lookAt, lookFrom, lookUp, fov);

    //read in DirectionToLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.directionToLight  = vec3(stof(inOne), stof(inTwo), stof(inThree));

    //read in LightColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.lightColor = vec3(stof(inOne), stof(inTwo), stof(inThree));

    //read in AmbientLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.ambientLight = vec3(stof(inOne), stof(inTwo), stof(inThree));

    //read in BackgroundColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.ambientLight = vec3(stof(inOne), stof(inTwo), stof(inThree));

    //read in objects loop
    while(fin.peek() != EOF)
    {
        //read in the comment garbage
        string comment1, comment2, comment3,  objType;
        fin >> comment1 >> comment2 >> comment3;

        //read in the object type
        fin >> objType;

        //we need to know to import the right data for a Sphere
        if (objType == "Sphere")
        {
            sphere inputSphere;
            //read in sphere center
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputSphere.center = vec3(stof(inOne), stof(inTwo), stof(inThree));

            //read in radius
            fin >> garbage >> inOne;
            inputSphere.radius = stof(inOne);

            //read in Kd
            fin >> garbage >> inOne;
            inputSphere.Kd = stof(inOne);

            //read in Ks
            fin >> garbage >> inOne;
            inputSphere.Ks = stof(inOne);

            //read in Ka
            fin >> garbage >> inOne;
            inputSphere.Ka = stof(inOne);

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputSphere.Od = vec3(stof(inOne), stof(inTwo), stof(inThree));

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputSphere.Os = vec3(stof(inOne), stof(inTwo), stof(inThree));

            //read in Kgls
            fin >> garbage >> inOne;
            inputSphere.Kgls = stof(inOne);

            sceneInfo.addSphere(inputSphere);

        }


    }




}

#endif //RAY_TRACER_SCENE_IMPORTER_H
