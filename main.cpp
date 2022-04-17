#include <fstream>
#include <cmath>

#include "models.h"
#include "funcs.h"

const int width = 1920, height = 1080;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Use this with ./Renderer <input file>\n";
        std::cout << "Format of input file described in the readme.\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if(!input.is_open())
    {
        std::cout << "Couldn't open " << argv[1] << "\n";
    }

    Camera myCamera = readCamera(input);
    std::vector<Surface> mySurfaces = readSurfaces(input);

    std::cout << "Making camera matrix\n";
    Eigen::MatrixXd myCameraMatrix = cameraMatrix(
        rotationMatrix(myCamera.get_angles()),
        myCamera.get_position());
    std::cout << myCameraMatrix << "\n";
    
    std::cout << "Transforming\n";
    for(size_t i = 0; i < mySurfaces.size(); ++i)
    {
        mySurfaces[i].transform(myCameraMatrix);
    }

    std::ofstream render("render.ppm");
    render << "P3\n";
    render << width << " " << height << "\n";
    render << "255\n";

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            std::vector<size_t> indices;

            double x1 = (double)x - (((double)width-1.0) / 2.0);
            double x2 = -1.0 * ((double)y - (((double)height-1.0) / 2.0));

            for(size_t i = 0; i < mySurfaces.size(); ++i)
            {
                if(mySurfaces[i].isInside(Eigen::Vector2d(x1, x2)))
                {
                    indices.push_back(i);
                }
            }
            
            if(indices.size() >= 1)
            {
                // if more than one surface present on a pixel, use the
                // earliest one
                // std::cout << mySurfaces[indices[0]].get_colors() << "\n";
                render << mySurfaces[indices[0]].get_colors() << "\n";
            }
            else
            {
                // white
                render << "255 255 255\n";
            }
        }
    }
}
