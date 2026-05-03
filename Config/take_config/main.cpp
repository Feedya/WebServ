#include "head.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "filename" << std::endl;
        return (0);
    }
    else
    {
        take_config(argv[1]);
    }
}