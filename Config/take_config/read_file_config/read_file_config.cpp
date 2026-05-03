#include "../head.hpp"

//cette fonction va renvoyer une std::string avec le contenu de mon fichier .conf
std::string read_filename(std::string filename)
{
    std::ifstream fd;
    //classe dans cpp
    //qui sert manipuler des chaines de charactere
    //en gros c est une classe tampon ou dedans on peut envoyer
    //avec << depuis un stream
    std::stringstream buffer;

    fd.open(filename.c_str());
    if (fd.fail() == true)
    {
        //std::cerr est pour les erreurs
        std::cerr << "on a pas reussis a ouvrir le fichier dans read_filename" << std::endl;
        exit (1);
    }

    buffer << fd.rdbuf();
    fd.close();
    return (buffer.str());
}

std::vector<std::string> create_vector(std::string buffer)
{
    std::string line;
    std::vector<std::string> file_vector;
    //on recreer un fd sur le buffer
    std::stringstream fd(buffer);
    
    //on va lire ligne par ligne depuis le fd
    while(std::getline(fd, line))
    {
        file_vector.push_back(line);
    }
    return (file_vector);
}

std::vector<std::string>    read_file_config(std::string filename)
{
    std::string buffer;
    std::vector<std::string> file_vector;

    buffer = read_filename(filename);
    file_vector = create_vector(buffer);


    return file_vector;
}