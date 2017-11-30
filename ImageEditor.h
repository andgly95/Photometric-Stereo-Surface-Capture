//
//  ImageEditor.h
//
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include "Sphere.h"
#include "image.h"


using namespace ComputerVisionProjects;

/**
 * @class ImageEditor
 * @brief A class that points to an Image object and supports operations for finding light values and surface normals in the image
 * @details
 * This object contains a pointer to an image object and contains methods that allow for obtaining light rays from a sphere
 * and using the light rays to detect the surface normals and albedos for points in the image, and drawing them onto the image.
 */

class ImageEditor {
private:
    Image *activeImage;
    Sphere *activeSphere;
    ThreeDVector* light_ray;

    
public:
    
    ImageEditor();
    
    /**
     *  Parameterized Constructor
     * @param addImage, takes a pointer to an image and sets the image as the active image
     * @post creates the ImageEditor object with the referenced Image loaded
     **/
    
    ImageEditor(Image *addImage);
    
    Image* getImage(){
        return activeImage;
    }
    
    Sphere* getSphere(){
        return activeSphere;
    }
    ThreeDVector* getLightRay(){
        return light_ray;
    }
    
    /**
     *  Binary Converter
     * @param threshhold the minimum value a pixel must be to register as an object
     * @post the image is converted into a binary image where background pixels are a 0 and objects are a 1
     **/
    
    void binaryConverter(int threshhold);
    
    /**
     *  Find Sphere
     * @param outputParams The text file to write the sphere to
     * @pre activeImage must be a binary image containing a sphere
     * @post the center and radius of the sphere are calculated and used to create a sphere object, that is then output to a file
     * @call writeSphere
     **/
    
    int findSphere(std::string outputParams);
    
    /**
     *  Read Sphere
     * @param input_sphere The text file to read the sphere from
     * @pre the text file must contain the center x, center y and radius of the sphere, separated by a space
     * @post the center and radius of the sphere are read and used to create a sphere object
     **/
    
    int readSphere(std::string input_sphere);
    
    /**
     *  Write Sphere
     * @param output_sphere The text file to write the sphere to
     * @pre the image editor must contain an active sphere
     * @post the sphere object is output to a file, with the center x, center y and radius of the sphere separated by a space
     **/
    
    void writeSphere(std::string output_sphere);
    
    /**
     *  Find Light Vector
     * @pre the image editor must contain a Sphere object and an image of the sphere with a light source
     * @post uses the brightest point on the sphere to calculate the vector of the light source, with the length equal to the brightness
     *   of the light source
     **/
    
    void findLightVector();
    
    /**
     *  Read Directions
     * @param &input_directions Reference to the input stream for the directions file,
     * @pre the text file must contain the x y and z values of the light source, separated by a space
     * @post the directions are read and used to create a light ray
     **/
    
    void readDirections(std::ifstream &input_directions);
    
    /**
     *  Write Directions
     * @param &output_directions Reference to the output stream for the directions file
     * @pre the image editor must contain an active sphere with a light ray
     * @post the directons for the vector of the light ray are output to a file, with the x y and z values separated by a space
     **/
    
    void writeDirections(std::ofstream &output_directions);
    
    /**
     *  Needle Map
     * @param map2 a pointer to the image of the second lighted image
     * @param light2 a pointer to the light vector of the second image
     * @param map3 a pointer to the image of the third lighted image
     * @param light3 a pointer to the light vector of the third image
     * @param step, the distance between the points measured for the needle map
     * @param thresh, the minimum brightness level a point must have in all images to check for normal
     * @pre the image editor must be loaded with the first lighted image and light vector
     * @algorithm the vector of light intensities at each point is multiplied by the inverse matrix the light sources to get the normal vector
     * @post on each point measured, a line is drawn representing the normal vector at the point
     **/
    
    void needleMap(Image *map2, ThreeDVector *light2, Image *map3, ThreeDVector *light3, int step, int thresh);
    
    /**
     *  Albedo Map
     * @param map2 a pointer to the image of the second lighted image
     * @param light2 a pointer to the light vector of the second image
     * @param map3 a pointer to the image of the third lighted image
     * @param light3 a pointer to the light vector of the third image
     * @param thresh, the minimum brightness level a point must have in all images to check for brightness
     * @pre the image editor must be loaded with the first lighted image and light vector
     * @algorithm the intensities at each point is set to the magnitude of the normal vector
     * @post on each point measured, the brightness is set to the albedo of the point
     **/
    
    void albedoMap(Image *map2, ThreeDVector *light2, Image *map3, ThreeDVector *light3, int thresh);
    
};

#endif /* ImageEditor_hpp */
