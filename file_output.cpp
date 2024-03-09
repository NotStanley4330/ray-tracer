//
// Created by starw on 2/21/2024.
//
#include "file_output.h"
#include <fstream>
#include <iostream>

using namespace std;
void outputToFile(vec3** colorData, int width, int height, int maxColors)
{
    ofstream outfile("C:\\Users\\starw\\CLionProjects\\ray_tracer\\pt2s2_output.ppm");

    outfile << "P3\n" << width << " " << height << "\n255\n";

    //write pixel data
    for(int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int intR = static_cast<int>(255.999 * colorData[x][y].x);
            int intG = static_cast<int>(255.999 * colorData[x][y].y);
            int intB = static_cast<int>(255.999 * colorData[x][y].z);

            outfile << intR << " " << intG << " " << intB << "\n";
        }
    }

    outfile.close();

    cout << "PPM file successfully written!" << endl;
}

