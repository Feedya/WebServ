#include "../head.hpp"

int take_config(char *filename)
{
    std::vector<std::string> file_vector;

    if (test_filename(filename) == 1)
    {
        std::cout << "mauvais filename" << std::endl;
        //faut voir se que je met ici en  sois on a rien new donc on peut exit
        exit (1);
    }
    file_vector = read_file_config(filename);
    return (0);
}