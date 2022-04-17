#include <iostream>
#include <vector>
#include <string>
#include <eigen3/Eigen/Dense>

class Surface
{
    // homogeneous coordinates.
    // NOT A VECTOR, just use the Eigen3 object to store.
    std::vector<Eigen::VectorXd> vertices;
    // surface color
    uint8_t r = 0, g = 0, b = 0;

    public:

    // simple constructors, one with colors in
    Surface(const std::vector<Eigen::VectorXd>& v_in,
            uint8_t r_in, uint8_t g_in, uint8_t b_in)
    {
        vertices = v_in;
        
        r = r_in; g = g_in; b = b_in;
    }

    // and one that defaults to black
    Surface(const std::vector<Eigen::VectorXd>& v_in)
    {
        vertices = v_in;
    }

    // transform each vertex with matrix A.
    // Used to apply camera matrix.
    // This rotates and translates the coordinates
    // into camera-centred coordinates
    // and projects them onto the camera plane.
    void transform(const Eigen::MatrixXd& A)
    {
        if(A.cols() != 4)
        {
            std::cout << "A has " << A.cols()
                      << " columns while vertices have 4 rows.\n";
            return;
        }

        for(size_t i = 0; i < vertices.size(); ++i)
        {
            std::cout << "Multiplying\n" << A << "\nand\n" << vertices[i] << "\n";
            vertices[i] = A * vertices[i];
            // std::cout << "Scaling:\n" << vertices[i] << "\n";
            // vertices[i] = vertices[i] / vertices[i](2);
            std::cout << "Result:\n" << vertices[i] << "\n\n";
        }
    }

    // this function adapted from https://stackoverflow.com/a/43896965
    // uses the ray casting algorithm
    bool isInside(const Eigen::Vector2d& point)
    {
        bool inside = false;

        for (size_t i = 0; i < vertices.size(); ++i)
        {
            // i is the index of the first vertex, j is the next one.
            // The original code uses a too-clever trick for this.
            size_t j = (i + 1) % vertices.size();

            // The vertices of the edge we are checking.
            double x1_0 = vertices[i](0);
            double x2_0 = vertices[i](1);
            double x1_1 = vertices[j](0);
            double x2_1 = vertices[j](1);

            // Check whether the edge intersects a line from (-inf,x2) to (x1,x2).

            // First check if the line crosses the horizontal line at x2 in either direction.
            if (((x2_0 <= point(1)) && (x2_1 > point(1))) || 
                ((x2_1 <= point(1)) && (x2_0 > point(1))))
            {
                // If so, get the point where it crosses that line. This is a simple solution
                // to a linear equation. Note that we can't get a division by zero here -
                // if x2_1 == x2_0 then the above if be false.
                double cross = (x1_1 - x1_0) * (point(1) - x2_0) / (x2_1 - x2_0) + x1_0;

                // Finally check if it crosses to the left of our test point. You could equally
                // do right and it should give the same result.
                if (cross < point(0))
                {
                    inside = !inside;
                }
            }
        }
        return inside;
    }

    std::string get_colors()
    {
        // std::cout << r << " " << g << " " << b << "\n";
        return std::to_string(r) + " " + std::to_string(g) +
                 " " + std::to_string(b);
    }
};

class Camera
{
    Eigen::Vector3d position;
    std::vector<double> angles;

    public:

    // simple constructor
    Camera(const Eigen::VectorXd& pos_in,
           const std::vector<double>& angle_in)
    {
        position = pos_in;
        angles = angle_in;
    }

    Eigen::Vector3d get_position()
    {
        return position;
    }

    std::vector<double> get_angles()
    {
        return angles;
    }
};
