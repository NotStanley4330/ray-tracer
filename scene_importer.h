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
    myCamera.lookAt.x = stof(inOne);
    myCamera.lookAt.y = (float) stoi(inTwo);
    myCamera.lookAt.z = (float) stoi(inThree);

    //read in CameraLookFrom
    fin>> garbage >> inOne >> inTwo >> inThree;
    myCamera.lookFrom.x = (float) stoi(inOne);
    myCamera.lookFrom.y = (float) stoi(inTwo);
    myCamera.lookFrom.z = (float) stoi(inThree);

    //read in CameraLookUp
    fin>> garbage >> inOne >> inTwo >> inThree;
    myCamera.lookUp.x = (float) stoi(inOne);
    myCamera.lookUp.y = (float) stoi(inTwo);
    myCamera.lookUp.z = (float) stoi(inThree);
    //read in FieldOfView
    fin>> garbage >> inOne;
    myCamera.fov = (float) stoi(inOne);

    //read in DirectionToLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.directionToLight.x = stof(inOne);
    sceneInfo.directionToLight.y = stof(inTwo);
    sceneInfo.directionToLight.z = stof(inThree);

    //read in LightColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.lightColor.x = stof(inOne);
    sceneInfo.lightColor.y = stof(inTwo);
    sceneInfo.lightColor.z = stof(inThree);

    //read in AmbientLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.ambientLight.x = stof(inOne);
    sceneInfo.ambientLight.y = stof(inTwo);
    sceneInfo.ambientLight.z = stof(inThree);

    //read in BackgroundColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.backgroundColor.x = stof(inOne);
    sceneInfo.backgroundColor.y = stof(inTwo);
    sceneInfo.backgroundColor.z = stof(inThree);

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
            vec3 centerVec(stof(inOne), stof(inTwo), stof(inThree));
            inputSphere.center = centerVec;

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
            vec3 odValue(stof(inOne), stof(inTwo), stof(inThree));
            inputSphere.Od = odValue;

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            vec3 osValue(stof(inOne), stof(inTwo), stof(inThree));
            inputSphere.Os = osValue;

            //read in Kgls
            fin >> garbage >> inOne;
            inputSphere.Kgls = stof(inOne);

            sceneInfo.addSphere(inputSphere);





        }


    }




}

#endif //RAY_TRACER_SCENE_IMPORTER_H
