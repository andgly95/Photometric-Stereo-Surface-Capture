//
//  s2.cpp
//
// Computes the directions and intensities of the light sources
//
//  Created by Andrew Glyadchenko on 11/20/17.
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
    
    if (argc!=6) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_parameters(argv[1]);
    const string image1(argv[2]);
    const string image2(argv[3]);
    const string image3(argv[4]);
    const string output_file(argv[5]);
    
    
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

    image_editor_1.readSphere(input_parameters);
    image_editor_2.readSphere(input_parameters);
    image_editor_3.readSphere(input_parameters);

    image_editor_1.findLightVector();
    image_editor_2.findLightVector();
    image_editor_3.findLightVector();
    
    ofstream direction_output;
    direction_output.open(output_file);
    image_editor_1.writeDirections(direction_output);
    image_editor_2.writeDirections(direction_output);
    image_editor_3.writeDirections(direction_output);
    direction_output.close();

    
}

