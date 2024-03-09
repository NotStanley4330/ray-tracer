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
    fin.open("C:\\Users\\starw\\CLionProjects\\ray_tracer\\pt2_scene3.txt", fstream::in);


    //start reading in input, these are just throw away variables
    string garbage, inOne, inTwo, inThree;


    //read in CameraLookAt
    fin >> garbage >> inOne >> inTwo >> inThree;
    vec3 lookAt(stod(inOne), stod(inTwo), stod(inThree));

    //read in CameraLookFrom
    fin>> garbage >> inOne >> inTwo >> inThree;
    vec3 lookFrom(stod(inOne), stod(inTwo), stod(inThree));

    //read in CameraLookUp
    fin>> garbage >> inOne >> inTwo >> inThree;
    vec3 lookUp(stod(inOne), stod(inTwo), stod(inThree));

    //read in FieldOfView
    fin>> garbage >> inOne;
    float fov = stod(inOne);

    myCamera = camera(lookAt, lookFrom, lookUp, fov);

    //read in DirectionToLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.directionToLight  = vec3(stod(inOne), stod(inTwo), stod(inThree));

    //read in LightColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.lightColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

    //read in AmbientLight
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.ambientLight = vec3(stod(inOne), stod(inTwo), stod(inThree));

    //read in BackgroundColor
    fin >> garbage >> inOne >> inTwo >> inThree;
    sceneInfo.backgroundColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

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
            inputSphere.center = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in radius
            fin >> garbage >> inOne;
            inputSphere.radius = stod(inOne);

            //read in Kd
            fin >> garbage >> inOne;
            inputSphere.diffuseCoeff = stod(inOne);

            //read in Ks
            fin >> garbage >> inOne;
            inputSphere.specularCoeff = stod(inOne);

            //read in Ka
            fin >> garbage >> inOne;
            inputSphere.ambeintCoeff = stod(inOne);

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputSphere.diffuseColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputSphere.specularColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in Kgls
            fin >> garbage >> inOne;
            inputSphere.glossCoeff = stod(inOne) * (float)0.2;

            fin >> garbage >> inOne;
            inputSphere.reflectivity = stod(inOne);

            sceneInfo.addSphere(inputSphere);

        }
        else if (objType == "Triangle")
        {
            triangle inputPolygon;

            //read in points
            fin >> inOne >> inTwo >> inThree;//point zero
            inputPolygon.points[0] = vec3(stod(inOne), stod(inTwo), stod(inThree));
            //point one
            fin >> inOne >> inTwo >> inThree;
            inputPolygon.points[1] = vec3(stod(inOne), stod(inTwo), stod(inThree));
            fin >> inOne >> inTwo >> inThree;//point two
            inputPolygon.points[2] = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in Kd
            fin >> garbage >> inOne;
            inputPolygon.diffuseCoeff = stod(inOne);

            //read in Ks
            fin >> garbage >> inOne;
            inputPolygon.specularCoeff = stod(inOne);

            //read in Ka
            fin >> garbage >> inOne;
            inputPolygon.ambeintCoeff = stod(inOne);

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputPolygon.diffuseColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in Od
            fin >> garbage >> inOne >> inTwo >> inThree;
            inputPolygon.specularColor = vec3(stod(inOne), stod(inTwo), stod(inThree));

            //read in Kgls
            fin >> garbage >> inOne;
            inputPolygon.glossCoeff = stod(inOne) * (float)0.2;

            fin >> garbage >> inOne;
            inputPolygon.reflectivity = stod(inOne);

            inputPolygon.setTrianglePlane();
            sceneInfo.addPolygon(inputPolygon);

        }


    }




}

#endif //RAY_TRACER_SCENE_IMPORTER_H
