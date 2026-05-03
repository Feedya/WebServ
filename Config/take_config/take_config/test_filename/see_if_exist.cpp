#include "../../head.hpp"

int see_if_exist(std::string filename)
{
    std::ifstream fd;

    fd.open(filename.c_str());

    if (fd.fail() == true)
    {
        std::cout << "le fichier n existe ppas" << std::endl;
        return (1);   
    }
    fd.close();
    return (0);
}
