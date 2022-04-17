# From_Scratch_Renderer
This program takes a camera position and angle and a 
    list of surfaces (defined by vertices and a color), and renders them.
This program built without premade rendering libraries, only using standard libraries
    and Eigen3 for handling matrices.

HOW TO USE:

Coordinate system is (x1,x2,x3) where x3 will become the axis the camera looks down.
Don't worry too much about this, but note that the coordinate system is left handed, unlike
    the system you may be used to.
    Here is an illustration of this, from wikipedia: https://en.wikipedia.org/wiki/Pinhole_camera_model#/media/File:Pinhole.svg
    The image plane, f, and P can be ignored.

The default camera angle, which angles will be added to, is 
    looking down the x3 axis, with x2 directly up and x1 directly to the right.
The x1 angle can be considered pitch, x2 angle yaw, and x3 roll.

Note that vertices MUST be coplanar. These are surfaces, not objects.
Vertices also MUST be listed in an order which connects the vertices properly.
E.g. (0,0,0) (0,1,0) (1,1,0) (1,0,0) creates a square,
    (0,0,0) (0,1,0) (1,0,0) (1,1,0) creates 3 lines.
all numbers except colors and # of surfaces/vertices are doubles. colors and # of surfaces/vertices are integers

Create a text file where surfaces have the following format, 
    with 0 <= R/G/B <= 255:

<camera position> <rotation about x1> <rotation about x2> <rotation about x3>
<# of surfaces>
<# of vertices> <VERTICES> C <R> <G> <B>

Example camera placed at 0,0,0 with 0 for all angles.
Example surface with vertices at (0,0,0), (5,0,0), (5,5,0), and (0,5,0)
    and color full red.
0,0,0 0 0 0
1
4 0,0,5 5,0,5 5,5,5 0,5,5 C 255 0 0

Structure of this repo:
all models and accompanying functions are found in models.h

declarations of non-class functions are found in funcs.h, and the 
    implementations are found in math.cpp and io.cpp
    the location of each implementation is noted in funcs.h