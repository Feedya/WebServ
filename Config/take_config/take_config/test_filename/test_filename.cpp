#include "../../head.hpp"

int test_filename(char *filename_char)
{
    if (filename_char == NULL)
        return (0);

    std::string filename = filename_char;
    std::string extension = ".conf";

    //on verifie si notre filename se finit par .conf
    if (filename.length() > extension.length()) 
    {
        if (compare_end(filename, extension) == 1)
            return (1);
        if (see_if_exist(filename) == 1)
            return (1);
    }
    return (0);
}