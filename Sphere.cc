//
//  Sphere.cpp
//  
//
//  Created by Andrew Glyadchenko on 11/20/17.
//

#include "Sphere.h"

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

Sphere::Sphere(double center_x, double center_y, double radius){
    center_x_ = center_x;
    center_y_ = center_y;
    radius_ = radius;
}

ThreeDVector* Sphere::normalVector(int global_point_x, int gloabal_point_y){
    double local_x = global_point_x - center_x_;
    double local_y = gloabal_point_y - center_y_;
    double local_z = -sqrt((radius_ * radius_) - (local_x * local_x) - (local_y * local_y));
    ThreeDVector* normalVector = new ThreeDVector;
    normalVector->x = local_x;
    normalVector->y = local_y;
    normalVector->z = local_z;
    return normalVector;
}

ThreeDVector* Sphere::scaleVector(double scale, ThreeDVector* ray){
    ThreeDVector* scaledVector;
    if (ray->x < 0){
        ray->x = -sqrt((ray->x * ray->x) * (scale * scale) / (radius_ * radius_));
    }
    else {
        ray->x = sqrt((ray->x * ray->x) * (scale * scale) / (radius_ * radius_));
    }
    if (ray->y < 0){
        ray->y = -sqrt((ray->y * ray->y) * (scale * scale) / (radius_ * radius_));
    }
    else{
        ray->y = sqrt((ray->y * ray->y) * (scale * scale) / (radius_ * radius_));
    }
    ray->z = -sqrt((ray->z * ray->z) * (scale * scale) / (radius_ * radius_));
    return ray;
}
