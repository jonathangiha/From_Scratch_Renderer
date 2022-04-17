// implemented and described in math.cpp
Eigen::Matrix3d rotationMatrix(const std::vector<double>& angles);

// implemented and described in math.cpp
Eigen::MatrixXd cameraMatrix(const Eigen::Matrix3d& rotationMatrix, 
                             const Eigen::Vector3d& cameraCoords);

// implemented in io.cpp
Camera readCamera(std::istream& is);

// implemented in io.cpp
std::vector<Surface> readSurfaces(std::istream &is);
