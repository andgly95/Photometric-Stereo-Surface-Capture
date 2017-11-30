//
//  s3.cpp
//
// Computes the surface normals of the object
//
//  Created by Andrew Glyadchenko on 11/21/17.
//
//

#include "ImageEditor.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    
    if (argc!=8) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_directions(argv[1]);
    const string image1(argv[2]);
    const string image2(argv[3]);
    const string image3(argv[4]);
    const string step(argv[5]);
    const string threshold(argv[6]);
    const string output_file(argv[7]);
    
    int stepValue = stoi(step,nullptr,10);
    int thresholdValue = stoi(threshold,nullptr,10);
    
    Image image_1;
    Image image_2;
    Image image_3;
    
    if (!ReadImage(image1, &image_1)) {
        cout <<"Can't open file " << image1 << endl;
        return 0;
    }
    
    if (!ReadImage(image2, &image_2)) {
        cout <<"Can't open file " << image2 << endl;
        return 0;
    }
    
    if (!ReadImage(image3, &image_3)) {
        cout <<"Can't open file " << image3 << endl;
        return 0;
    }
    
    
    Image *imageReference1 = &image_1;
    Image *imageReference2 = &image_2;
    Image *imageReference3 = &image_3;

    ImageEditor image_editor_1(imageReference1);
    ImageEditor image_editor_2(imageReference2);
    ImageEditor image_editor_3(imageReference3);

    
    ifstream direction_input;
    direction_input.open(input_directions);
    image_editor_1.readDirections(direction_input);
    image_editor_2.readDirections(direction_input);
    image_editor_3.readDirections(direction_input);
    direction_input.close();
    image_editor_1.needleMap(imageReference2,image_editor_2.getLightRay(),imageReference3,image_editor_3.getLightRay(),stepValue,thresholdValue);

    if (!WriteImage(output_file, image_1)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}

