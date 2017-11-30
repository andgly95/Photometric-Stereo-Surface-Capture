//
//  ImageEditor.cpp
//  
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#include "ImageEditor.h"
#include "image.h"
#include "Sphere.h"

#include <cstdio>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

ImageEditor::ImageEditor(){
    activeImage = nullptr;
    activeSphere = nullptr;
    light_ray = nullptr;
}



ImageEditor::ImageEditor(Image *addImage){
    activeImage = addImage;
}

void ImageEditor::binaryConverter(int threshhold){
    for (int i=0;i<activeImage->num_rows();i++){
        for (int j=0;j<activeImage->num_columns();j++){
            if (activeImage->GetPixel(i,j) < threshhold){
                activeImage->SetPixel(i,j,0);
            }
            else if (activeImage->GetPixel(i,j) >= threshhold){
                activeImage->SetPixel(i,j,1);
            }
        }
    }
    activeImage->SetNumberGrayLevels(1);
    return;
}

int ImageEditor::findSphere(string outputParams){
    bool foundCircle = 0;
    int min_row, max_row;
    int min_col, max_col;
    double area = 0;
    double centerX = 0;
    double centerY = 0;
    for (int i=0;i<activeImage->num_rows();i++){
        for (int j=0;j<activeImage->num_columns();j++){
            if(activeImage->GetPixel(i,j)==1){
                if (foundCircle == 0){
                    min_row = i;
                    max_row = i;
                    min_col = j;
                    max_col = j;
                    foundCircle = 1;
                }
                else{
                    if (max_row < i){
                        max_row = i;
                    }
                    if (min_col > j){
                        min_col = j;
                    }
                    if (max_col < j){
                        max_col = j;
                    }
                }
                area++;
                
                centerX += i;
                centerY += j;
            }
        }
    }
    
    
    centerX = centerX / area;
    centerY = centerY / area;
    double width = max_col - min_col;
    double length = max_row - min_row;
    double radius = (width + length) / 4;
    
    activeSphere = new Sphere(centerX,centerY,radius);
    writeSphere(outputParams);
    
    
    cout << "Width is " << width << " and Length is " << length << endl;

    cout << "Radius is " << radius << endl;
    
    return 1;
}

int ImageEditor::readSphere(string input_sphere){

    ifstream readsphere;
    readsphere.open(input_sphere);

    
    double center_x, center_y, radius;
    readsphere >> center_x;
    readsphere >> center_y;
    readsphere >> radius;

    activeSphere = new Sphere(center_x,center_y,radius);
    
    readsphere.close();
    return 1;
}

void ImageEditor::writeSphere(string output_sphere){
    ofstream writesphere;
    writesphere.open(output_sphere);
    writesphere << activeSphere->center_x_ << " " << activeSphere->center_y_ << " " << activeSphere->radius_;
    writesphere.close();
}
void ImageEditor::findLightVector(){
    int max_bright_x, max_bright_y;
    int max_bright = 0;
    for (int i=0;i<activeImage->num_rows();i++){
        for (int j=0;j<activeImage->num_columns();j++){
            if(activeImage->GetPixel(i,j) > max_bright){
                max_bright = activeImage->GetPixel(i,j);
                max_bright_x = i;
                max_bright_y = j;
            }
        }
    }
    cout << "\nThe brightest point is "<<max_bright<<" at ("<< max_bright_x<<" , "<<max_bright_y<< ")\n";
    ThreeDVector* brightestNormal = activeSphere->normalVector(max_bright_x,max_bright_y);
    cout << "\nThe normal vector is " << brightestNormal->x << " " << brightestNormal->y << " " << brightestNormal->z << endl;
    ThreeDVector* lightRay = activeSphere->scaleVector(double(max_bright), brightestNormal);
    cout << "\nThe light ray is " << lightRay->x << " " << lightRay->y << " " << lightRay->z << endl;
    activeSphere->light_ray = lightRay;
}

void ImageEditor::readDirections(ifstream &input_directions){
    double xValue, yValue, zValue;
    input_directions >> xValue;
    input_directions >> yValue;
    input_directions >> zValue;
    light_ray = new ThreeDVector;
    light_ray->x = xValue;
    light_ray->y = yValue;
    light_ray->z = zValue;
}

void ImageEditor::writeDirections(ofstream &output_directions){
    output_directions << activeSphere->light_ray->x << " " << activeSphere->light_ray->y << " " << activeSphere->light_ray->z << endl;
}

void ImageEditor::needleMap(Image *map2, ThreeDVector *light2, Image *map3, ThreeDVector *light3, int step, int thresh){
    Image *map1 = activeImage;
    ThreeDVector *light1 = light_ray;
    
    double **light_matrix = new double*[3];
    light_matrix[0] = new double[3];
    light_matrix[0][0] = light1->x;
    light_matrix[0][1] = light1->y;
    light_matrix[0][2] = light1->z;
    light_matrix[1] = new double[3];
    light_matrix[1][0] = light2->x;
    light_matrix[1][1] = light2->y;
    light_matrix[1][2] = light2->z;
    light_matrix[2] = new double[3];
    light_matrix[2][0] = light3->x;
    light_matrix[2][1] = light3->y;
    light_matrix[2][2] = light3->z;
    
    double** minor_matrix = new double*[3];
    minor_matrix[0] = new double[3];
    minor_matrix[0][0] = (light_matrix[1][1] * light_matrix[2][2]) - (light_matrix[1][2] * light_matrix[2][1]);
    minor_matrix[0][1] = -((light_matrix[1][0] * light_matrix[2][2]) - (light_matrix[1][2] * light_matrix[2][0]));
    minor_matrix[0][2] = (light_matrix[1][0] * light_matrix[2][1]) - (light_matrix[1][1] * light_matrix[2][0]);
    minor_matrix[1] = new double[3];
    minor_matrix[1][0] = -((light_matrix[0][1] * light_matrix[2][2]) - (light_matrix[0][2] * light_matrix[2][1]));
    minor_matrix[1][1] = (light_matrix[0][0] * light_matrix[2][2]) - (light_matrix[0][2] * light_matrix[2][0]);
    minor_matrix[1][2] = -((light_matrix[0][0] * light_matrix[2][1]) - (light_matrix[0][1] * light_matrix[2][0]));
    minor_matrix[2] = new double[3];
    minor_matrix[2][0] = (light_matrix[0][1] * light_matrix[1][2]) - (light_matrix[0][2] * light_matrix[1][1]);
    minor_matrix[2][1] = -((light_matrix[0][0] * light_matrix[1][2]) - (light_matrix[0][2] * light_matrix[1][0]));
    minor_matrix[2][2] = (light_matrix[0][0] * light_matrix[1][1]) - (light_matrix[0][1] * light_matrix[1][0]);
    
    double** adj_matrix = new double*[3];
    adj_matrix[0] = new double[3];
    adj_matrix[0][0] = minor_matrix[0][0];
    adj_matrix[0][1] = minor_matrix[1][0];
    adj_matrix[0][2] = minor_matrix[2][0];
    adj_matrix[1] = new double[3];
    adj_matrix[1][0] = minor_matrix[0][1];
    adj_matrix[1][1] = minor_matrix[1][1];
    adj_matrix[1][2] = minor_matrix[2][1];
    adj_matrix[2] = new double[3];
    adj_matrix[2][0] = minor_matrix[0][2];
    adj_matrix[2][1] = minor_matrix[1][2];
    adj_matrix[2][2] = minor_matrix[2][2];
    
    
    
    double determinant = (light_matrix[0][0] * minor_matrix[0][0]) + (light_matrix[0][1] * minor_matrix[0][1]) + (light_matrix[0][2] * minor_matrix[0][2]);
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            adj_matrix[i][j] = adj_matrix[i][j] / determinant;
        }
    }
    
    cout << "DETERMINANT\n" << determinant << endl;
    
    cout << "ORIGINAL\n";
    cout << "|" << int(light_matrix[0][0]+.5) << "|" << int(light_matrix[0][1]+.5)  << "|" << int(light_matrix[0][2]+.5) << "|" << endl;
    cout << "|" << int(light_matrix[1][0]+.5) << "|" << int(light_matrix[1][1]+.5)  << "|" << int(light_matrix[1][2]+.5) << "|" << endl;
    cout << "|" << int(light_matrix[2][0]+.5) << "|" << int(light_matrix[2][1]+.5)  << "|" << int(light_matrix[2][2]+.5) << "|" << endl;
    
    cout << "MINORS\n";
    cout << "|" << (minor_matrix[0][0]) << "|" << (minor_matrix[0][1])  << "|" << (minor_matrix[0][2]) << "|" << endl;
    cout << "|" << (minor_matrix[1][0]) << "|" << (minor_matrix[1][1])  << "|" << (minor_matrix[1][2]) << "|" << endl;
    cout << "|" << (minor_matrix[2][0]) << "|" << (minor_matrix[2][1])  << "|" << (minor_matrix[2][2]) << "|" << endl;
    
    cout << "INVERSE\n";
    cout << "|" << (adj_matrix[0][0]) << "|" << (adj_matrix[0][1])  << "|" << (adj_matrix[0][2]) << "|" << endl;
    cout << "|" << (adj_matrix[1][0]) << "|" << (adj_matrix[1][1])  << "|" << (adj_matrix[1][2]) << "|" << endl;
    cout << "|" << (adj_matrix[2][0]) << "|" << (adj_matrix[2][1])  << "|" << (adj_matrix[2][2]) << "|" << endl;

    
    for (int i=0;i<activeImage->num_rows();i += step){
        for (int j=0;j<activeImage->num_columns();j+= step){
            double *intensity_vector = new double[3];
            
            
            
            intensity_vector[0] = map1->GetPixel(i,j);
            intensity_vector[1] = map2->GetPixel(i,j);
            intensity_vector[2] = map3->GetPixel(i,j);
            
            if(intensity_vector[0] > thresh && intensity_vector[1] > thresh && intensity_vector[2] > thresh){
                
                cout << "Intensity " << intensity_vector[0] << " " << intensity_vector[1] << " " << intensity_vector[2] << endl;

                
                double normal[3] = {0,0,0};

                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        normal[k] += (adj_matrix[k][l] * intensity_vector[l]);
                    }
                }
                double magnitude = sqrt((normal[0]*normal[0])+(normal[1]*normal[1])+(normal[2]*normal[2]));
                
                cout << "Magnitude: " << magnitude << endl;
                for(int l=0;l<3;l++){
                    normal[l] = normal[l] * 10 / magnitude;
                }
                DrawLine(i,j,int(i+normal[0]+.5),int(j+normal[1]+.5),255,activeImage);
                
                activeImage->SetPixel(i,j,0);
                activeImage->SetPixel(i-1,j-1,255);
                activeImage->SetPixel(i+1,j-1,255);
                activeImage->SetPixel(i-1,j+1,255);
                activeImage->SetPixel(i+1,j+1,255);
                
                cout << "Surface normal " << normal[0] << " " << normal[1] << " " << normal[2] << endl;
            }
        }
    }
}

void ImageEditor::albedoMap(Image *map2, ThreeDVector *light2, Image *map3, ThreeDVector *light3, int thresh){
    Image *map1 = activeImage;
    ThreeDVector *light1 = light_ray;
    
    cout << "WTFN\n";

    
    double **light_matrix = new double*[3];
    light_matrix[0] = new double[3];
    light_matrix[0][0] = light1->x;
    light_matrix[0][1] = light1->y;
    light_matrix[0][2] = light1->z;
    light_matrix[1] = new double[3];
    light_matrix[1][0] = light2->x;
    light_matrix[1][1] = light2->y;
    light_matrix[1][2] = light2->z;
    light_matrix[2] = new double[3];
    light_matrix[2][0] = light3->x;
    light_matrix[2][1] = light3->y;
    light_matrix[2][2] = light3->z;
    
    double** minor_matrix = new double*[3];
    minor_matrix[0] = new double[3];
    minor_matrix[0][0] = (light_matrix[1][1] * light_matrix[2][2]) - (light_matrix[1][2] * light_matrix[2][1]);
    minor_matrix[0][1] = -((light_matrix[1][0] * light_matrix[2][2]) - (light_matrix[1][2] * light_matrix[2][0]));
    minor_matrix[0][2] = (light_matrix[1][0] * light_matrix[2][1]) - (light_matrix[1][1] * light_matrix[2][0]);
    minor_matrix[1] = new double[3];
    minor_matrix[1][0] = -((light_matrix[0][1] * light_matrix[2][2]) - (light_matrix[0][2] * light_matrix[2][1]));
    minor_matrix[1][1] = (light_matrix[0][0] * light_matrix[2][2]) - (light_matrix[0][2] * light_matrix[2][0]);
    minor_matrix[1][2] = -((light_matrix[0][0] * light_matrix[2][1]) - (light_matrix[0][1] * light_matrix[2][0]));
    minor_matrix[2] = new double[3];
    minor_matrix[2][0] = (light_matrix[0][1] * light_matrix[1][2]) - (light_matrix[0][2] * light_matrix[1][1]);
    minor_matrix[2][1] = -((light_matrix[0][0] * light_matrix[1][2]) - (light_matrix[0][2] * light_matrix[1][0]));
    minor_matrix[2][2] = (light_matrix[0][0] * light_matrix[1][1]) - (light_matrix[0][1] * light_matrix[1][0]);
    
    double** adj_matrix = new double*[3];
    adj_matrix[0] = new double[3];
    adj_matrix[0][0] = minor_matrix[0][0];
    adj_matrix[0][1] = minor_matrix[1][0];
    adj_matrix[0][2] = minor_matrix[2][0];
    adj_matrix[1] = new double[3];
    adj_matrix[1][0] = minor_matrix[0][1];
    adj_matrix[1][1] = minor_matrix[1][1];
    adj_matrix[1][2] = minor_matrix[2][1];
    adj_matrix[2] = new double[3];
    adj_matrix[2][0] = minor_matrix[0][2];
    adj_matrix[2][1] = minor_matrix[1][2];
    adj_matrix[2][2] = minor_matrix[2][2];
    
    
    
    double determinant = (light_matrix[0][0] * minor_matrix[0][0]) + (light_matrix[0][1] * minor_matrix[0][1]) + (light_matrix[0][2] * minor_matrix[0][2]);
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            adj_matrix[i][j] = adj_matrix[i][j] / determinant;
        }
    }
    double maxMagnitude = 0;
    double** magnitudeMap = new double*[activeImage->num_rows()];
    for (int i=0;i<activeImage->num_rows();i++){
        magnitudeMap[i] = new double[activeImage->num_columns()];
        for (int j=0;j<activeImage->num_columns();j++){
            double *intensity_vector = new double[3];
            
            
            
            intensity_vector[0] = map1->GetPixel(i,j);
            intensity_vector[1] = map2->GetPixel(i,j);
            intensity_vector[2] = map3->GetPixel(i,j);
            
            if(intensity_vector[0] > thresh && intensity_vector[1] > thresh && intensity_vector[2] > thresh){
                
                cout << "Intensity " << intensity_vector[0] << " " << intensity_vector[1] << " " << intensity_vector[2] << endl;
                
                
                double normal[3] = {0,0,0};
                
                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        normal[k] += (adj_matrix[k][l] * intensity_vector[l]);
                    }
                }
                double magnitude = sqrt((normal[0]*normal[0])+(normal[1]*normal[1])+(normal[2]*normal[2]));
                if (magnitude > maxMagnitude){
                    maxMagnitude = magnitude;
                }
                magnitudeMap[i][j] = magnitude;
                activeImage->SetPixel(i,j,0);
                
            }
        }
    }
    for (int i=0;i<activeImage->num_rows();i++){
        for (int j=0;j<activeImage->num_columns();j++){
            
            activeImage->SetPixel(i,j,int(magnitudeMap[i][j] * 255 / maxMagnitude));
        }
        
    }
}
