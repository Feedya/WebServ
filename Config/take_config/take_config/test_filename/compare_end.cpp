#include "../../head.hpp"

int compare_end(std::string filename, std::string extension)
{
    int i = 0;
    int c = 0;
    //faut faire - 1 parceque la fonction size retourne la taille pas en index
    i = filename.size() - 1;
    c = 4;
    while (c >= 0 && filename[i] == extension[c])
    {
        i--;
        c--;
    }
    if (c == -1)
    {
        return (0);
    }
    return (1);
}