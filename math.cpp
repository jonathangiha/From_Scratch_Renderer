#include <cmath>

#include "models.h"
#include "funcs.h"

// create the rotation matrix for transforming to camera-centred coordinates
// This takes in the camera's angles, not the angles to be used to correct.
Eigen::Matrix3d rotationMatrix(const std::vector<double>& angles)
{
    if(angles.size() != 3)
    {
        std::cout << "there should be 3 angles but there are "
                  << angles.size() << ".\n";
    }
    // make x1 rotation matrix.
    Eigen::Matrix3d r_x1;
    double x1_cos = cos(angles[0]);
    double x1_sin = sin(angles[0]);

    r_x1(0,0) = 1;
    r_x1(0,1) = 0;
    r_x1(0,2) = 0;

    r_x1(1,0) = 0;
    r_x1(1,1) = x1_cos;
    r_x1(1,2) = -1 * x1_sin;

    r_x1(2,0) = 0;
    r_x1(2,1) = x1_sin;
    r_x1(2,2) = x1_cos;

    // make x2 rotation matrix.
    Eigen::Matrix3d r_x2;
    double x2_cos = cos(angles[1]);
    double x2_sin = sin(angles[1]);

    r_x2(0,0) = x2_cos;
    r_x2(0,1) = 0;
    r_x2(0,2) = x2_sin;

    r_x2(1,0) = 0;
    r_x2(1,1) = 1;
    r_x2(1,2) = 0;

    r_x2(2,0) = -1 * x2_sin;
    r_x2(2,1) = 0;
    r_x2(2,2) = x2_cos;

    // make x3 rotation matrix.
    Eigen::Matrix3d r_x3;
    double x3_cos = cos(angles[2]);
    double x3_sin = sin(angles[2]);

    r_x3(0,0) = x3_cos;
    r_x3(0,1) = -1 * x3_sin;
    r_x3(0,2) = 0;

    r_x3(1,0) = x3_sin;
    r_x3(1,1) = x3_cos;
    r_x3(1,2) = 0;

    r_x3(2,0) = 0;
    r_x3(2,1) = 0;
    r_x3(2,2) = 1;

    // return combined rotation matrix.
    std::cout << "Rotation matrix:\n" << r_x3 * r_x2 * r_x1 << "\n\n";
    return r_x3 * r_x2 * r_x1;
}

Eigen::MatrixXd cameraMatrix(const Eigen::Matrix3d& rotationMatrix, 
                             const Eigen::Vector3d& cameraCoords)
{
    // I_3 | -ñ
    Eigen::MatrixXd I_n(3,4);
    I_n(0,0) = 1;
    I_n(0,1) = 0;
    I_n(0,2) = 0;
    I_n(0,3) = -1 * cameraCoords(0);

    I_n(1,0) = 0;
    I_n(1,1) = 1;
    I_n(1,2) = 0;
    I_n(1,3) = -1 * cameraCoords(1);

    I_n(2,0) = 0;
    I_n(2,1) = 0;
    I_n(2,2) = 1;
    I_n(2,3) = -1 * cameraCoords(2);

    return rotationMatrix * I_n;
}
