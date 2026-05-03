#include <sys/socket.h> // Pour socket, bind, listen, accept
#include <netinet/in.h> // Pour sockaddr_in et htons
#include <sys/select.h> // Pour select et les macros FD_
#include <unistd.h>     // Pour close, read et write
#include <arpa/inet.h>  // Pour la manipulation des adresses IP
#include <ostream>
#include <iostream>

//je dois utiliser 
// pour appel systeme : socket() bind() et listen()
// pour la reception  : accept()
//
//--------------------------------------------------------------------------------------------------------
//
//c est quoi une socket : 
// c est comme un telephone mais qui n est pas encore brancher.

//--------------------------------------------------------------------------------------------------------
//
//socket()
//  la fonction socket va ouvrire une porte vers le reseaux qui sera le fd  
//  elle va nous donner un telephone mais sans numero et pas brancher
//
//    int socket(int domain, int type, int protocol);
//      
//      int domain : definie la "famille" de protocole (IPv4, IPv6, locales)
//                      nous on va utiliser AF_INET qui est le IPv4
//
//      int type : type de communication il y a le TCP(SOCK_STREAM) et le UDP(SOCK_DGRAM) nous on va utiliser le TCP
//      
//      int protocol : on va mettre le 0 comme ca le systeme choisis lui meme le protocol qui lui va
//
//--------------------------------------------------------------------------------------------------------
//
//bind()
//  bind va donner un numero a notre telephone et a le brancher
//  
//      int bind(int sockfd, const struct sockaddr ∗addr, socklen_t addrlen);
//
//          int sockfd : le fd qu on a eu grace a socket
//
//          const struct sockaddr *addr : structure sockaddr_in que l ont cast en sockaddr
//                                          cette structure va contenir le port et l ip
//                                          ca sera l adresse ou le fd va habiter
//
//          socklen_t addréen : taille en octets de la structure (sizeof(struct sockaddr_in))
//
//--------------------------------------------------------------------------------------------------------
//
//listen()
//  elle sert a creer une liste d attente des fd 
//
//      int listen(int sockfd, int backlog);
//          
//          int sockfd : notre fd qu on a creer avec socket() et qu on a brancher avec bind()
//
//          int backlog : la taille de notre file d attente.
//
//--------------------------------------------------------------------------------------------------------
//
// accept()
//  accept va prendre un fd et engager la communication avec
//
//      int accept(int sockfd, struct ssizeofockaddr ∗addr, socklen_t ∗addrlen);
//
//          int sockfd : le fd (client)
//
//          struct sockaddr *addr : pointeur sur une structure sockaddr vide que le systeme va remplir
//
//          socklen_t *addrlen : poniteur  sur un entier qui contient la taille  de *addr.
//
//--------------------------------------------------------------------------------------------------------


int compare(char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
    {    
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return (1);
    return (0);
}

int main()
{
    int error = 0;

    //creation de socket pas brancher
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //sockaddr_in est la structure pour le IPv4
    struct sockaddr_in adresse;

    //family de IPv4 comme on fait sur IPv4
    adresse.sin_family = AF_INET;

    //on ecoute sur toute les interfaces 
    //en gros le client peut venir de n importe ou(wifi, cable, reseaux local etc...)
    adresse.sin_addr.s_addr = INADDR_ANY;

    //htons va traduire le port en language que le systeme va comprendre
    adresse.sin_port = htons(8080);

    //on va connecter notre fd
    error = bind(fd, reinterpret_cast<sockaddr *>(&adresse), sizeof(adresse));
    if (error == -1)
    {
        std::cout << "erreur de bind" << std::endl;
        close (fd);
        return (-1);
    }
    
    //ici on creer notre portier on aura une queue max de 100 personne
    //qui vont se faire accepter par notre fd a rentrer 1 par 1
    error = listen(fd, 100);
    if (error == -1)
    {
        std::cout << "erreur de listen" << std::endl;
        close(fd);
        return (-1);
    }

    //on va accept le prochain client il lui faut une structure pour lui
    //et on va reservoir son fd
    while (1)
    {
        struct sockaddr_in adresse_client;
        socklen_t taille_client = sizeof(adresse_client);
        int new_fd = accept(fd, reinterpret_cast<sockaddr *>(&adresse_client), &taille_client);
        if (new_fd < 0)
        {
            std::cout << "Erreur de accept" << std::endl;
            close(fd);
            return (-1);
        }

        //mtn on va ajouter une fonctionaliter
        //pour que le client puisse nous envoyer du texte
        char buffer[1000];
        //on va utiliser la fonction recv qui est specifiquement faite
        //pour les socket, elle va lire se que la carte reseaux a ressus
        //et stoquer dans un buffer
        error = recv(new_fd, buffer, 1000, 0);
        if (error < 0)
        {
            std::cout << "erreur de recv" << std::endl;
            close(fd);
            close(new_fd);
            return (-1);
        }
        std::cout << buffer << std::endl;
        
        if (compare(buffer, "stop") == 1)
            break;
        //mtn on va envoyer une reponse au client
        char buffer2[] = "hello client";
        ssize_t bits = send(new_fd, buffer2, sizeof(buffer) - 1, 0);
        if (bits < 0)
        {
            std::cout << "send a bader" << std::endl;
            close(fd);
            close(new_fd);
            return (-1);
        }
    }

}