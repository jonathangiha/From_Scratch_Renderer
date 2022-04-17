#include "models.h"
#include "funcs.h"

// input
Camera readCamera(std::istream& is)
{
    std::string placeholder;

    double c_x1, c_x2, c_x3;

    getline(is, placeholder, ',');
    c_x1 = std::stod(placeholder);

    getline(is, placeholder, ',');
    c_x2 = std::stod(placeholder);

    getline(is, placeholder, ' ');
    c_x3 = std::stod(placeholder);

    std::cout << "Camera coordinates: " << c_x1 << " " << c_x2 << " " << c_x3 << "\n\n";

    double c_angle1, c_angle2, c_angle3;

    getline(is, placeholder, ' ');
    c_angle1 = std::stod(placeholder);

    getline(is, placeholder, ' ');
    c_angle2 = std::stod(placeholder);

    getline(is, placeholder, '\n');
    c_angle3 = std::stod(placeholder);

    std::cout << "Camera angles: " << c_angle1 << " " << c_angle2 << " " << c_angle3 << "\n\n";

    Eigen::Vector3d pos(c_x1, c_x2, c_x3);
    std::vector<double> angles{c_angle1, c_angle2, c_angle3};

    return Camera(pos, angles);
}

std::vector<Surface> readSurfaces(std::istream &is)
{
    // CHECK FOR COPLANAR
    int num_surface;
    is >> num_surface;

    std::vector<Surface> result;

    for(int i = 0; i < num_surface; ++i)
    {
        std::vector<Eigen::VectorXd> vertices;

        int num_vertices;
        is >> num_vertices;

        std::string placeholder;
        double x1, x2, x3;

        for(int j = 0; j < num_vertices; ++j)
        {
            getline(is, placeholder, ',');
            x1 = std::stod(placeholder);

            getline(is, placeholder, ',');
            x2 = std::stod(placeholder);

            getline(is, placeholder, ' ');
            x3 = std::stod(placeholder);

            // remember, we're in homogeneous coordinates
            vertices.push_back(Eigen::Vector4d(x1, x2, x3, 1));
        }

        getline(is, placeholder, ' ');
        std::cout << "C: " << placeholder << "\n";
        if(placeholder[0] != 'C')
        {
            std::cout <<
                "Incorrect format of input file. Please check readme.\n";
        }

        uint8_t red = 0, green = 0, blue = 0;

        getline(is, placeholder, ',');
        std::cout << "r: " << placeholder << "\n";
        red = (uint8_t)std::stoi(placeholder);

        getline(is, placeholder, ',');
        std::cout << "g: " << placeholder << "\n";
        green = (uint8_t)std::stoi(placeholder);

        getline(is, placeholder, '\n');
        std::cout << "b: " << placeholder << "\n";
        blue = (uint8_t)std::stoi(placeholder);

        result.push_back(Surface(vertices, red, green, blue));
    }

    return result;
}
