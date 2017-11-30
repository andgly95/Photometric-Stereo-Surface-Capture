//
//  Sphere.hpp
//  
//
//  Created by Andrew Glyadchenko on 11/20/17.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>

struct ThreeDVector{
    double x;
    double y;
    double z;
};

/**
 * @class Sphere
 * @brief A class that stores data about a sphere, and the light data for the light source
 * @details
 * This object contains stores the radius and center position of a sphere and contains methods to calculate and scale the normal vector
 * of the light source of the image
 */

class Sphere {
public:
    
    Sphere(double center_x, double center_y, double radius);
    double width_;
    double length_;
    double radius_;
    double center_x_;
    double center_y_;
    ThreeDVector* light_ray;
    
    /**
     *  Normal Vector
     * @param global_point_x global_point_y the image coordinates of the brightest point of the image
     * @return a 3D Vector of the light ray with the origin at the center of the sphere, and the magnitude equal to the radius
     **/
    
    ThreeDVector* normalVector(int global_point_x, int gloabal_point_y);
    
    /**
     *  Scele Vector
     * @param scale the magnitude to scale the ray to
     * @param ray the vector that is to be scaled to the brightness intensity of the source
     * @return a 3D Vector of the light ray with the origin at the center of the sphere, and the magnitude equal to the light intensity
     **/
    
    ThreeDVector* scaleVector(double scale, ThreeDVector* ray);
    
};



#endif /* Sphere_hpp */
