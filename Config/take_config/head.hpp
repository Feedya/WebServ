#ifndef  HEAD_HPP
#define HEAD_HPP

#include <sys/socket.h> // Pour socket, bind, listen, accept
#include <netinet/in.h> // Pour sockaddr_in et htons
#include <sys/select.h> // Pour select et les macros FD_
#include <unistd.h>     // Pour close, read et write
#include <arpa/inet.h>  // Pour la manipulation des adresses IP
#include <ostream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

int take_config(char *filename);
int test_filename(char *filename_char);
int see_if_exist(std::string filename);
int compare_end(std::string filename, std::string extension);
std::vector<std::string>    read_file_config(std::string filename);

#endif