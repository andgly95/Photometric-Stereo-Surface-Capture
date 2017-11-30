RRRR EEEE  AA  DDD    M   M EEEE
R  R E    A  A D  D   MM MM E
RRRR EEEE AAAA D  D   M M M EEEE
R R  E    A  A D  D   M   M E
R  R EEEE A  A DDD    M   M EEEE

Andrew Glyadchenko
Assignment 4

For this assignment I completed all four parts, which all work. I reengineered by ImageEditor class from my previous assignments to execute most of the tasks, adding methods for reading and writing the sphere and light direction attributes, finding the light vectors, and generating the needle and albedo maps for the object. I also used a Sphere class and a 3D Vector structure to store the light sources with methods to calculate and scale the normal vectors.

The first part of the assignment, s1 was easy to complete. After applying the binary converter used in the last two assignments, I wrote a findSphere() class to calculate the center coordinates and radius of the sphere and output them to the text file.

Part 2 was more complicated, as I had to import three sphere images, read in the radius and center from the text file, and find the normal of the brightest point of the sphere, which is equivalent to the light vector. To get the normal I wrote a method in the Sphere class to take in the x and y values of the brightest point in the image and convert them into 3d x y and z coordinates, relative to the center of the sphere. After that I used a method to scale the length of the vector to make it equal to the intensity of the light source. Then I output the directions of the light source of all three images to a file by passing the stream to a method on each image editor. 

The third part was the most difficult, as I had to read in the direction of the light in all three images, and generate the surface normals at each point based on the light intensities. To do that, I had to create a 3x3 matrix containing the 3 light vectors, compute the inverse, and multiply it by a vector with the intensities of the point under each light source. The output divided by it’s magnitude results in a normalized vector of the surface normal at the point. Implementing the matrix took a lot of work to figure out but eventually I got it to work accurately. Afterwards I scaled the vector by ten to get the x and y coordinates so I could draw the lines for the needle map.

Getting the last part was easy, I just had to copy the code used to get the magnitude, and store it in a matrix for each pixel in the image. After getting the maximum magnitude of the image, I scaled all the values to fall between 0 and 255, and wrote the magnitude to each pixel

The final output is nearly identical to the provided sample images, and my biggest difficulty was fixing some bugs including one where the vector scaler method would set all directions to positive resulting in inaccurate surface normals. Eventually, I got the desired outputs

The threshold values used for the test files are the following
s1: 
threshold - 100
s3:
threshold - 100
step - 10
s4:
threshold - 100

Problems 1 is also in this directory as JPGs

The programs should compile with the make all command.

For s1 the command to run is ./s1 inputsphere.pgm threshhold parameters.txt 

For s2 the command to run is ./s2 parameters.txt image1.pgm image2.pgm image3.pgm directions.txt 

For s3 the command to run is ./s3 directions.txt image1.pgm image2.pgm image3.pgm step threshold needleoutput.pgm 

For s4 the command to run is ./s4 directions.txt image1.pgm image2.pgm image3.pgm threshold albedooutput.pgm
