#ifndef SIMPLECHAT_CLIENTHANDLER_H
#define SIMPLECHAT_CLIENTHANDLER_H

#include "Server.h"
#define BUFFER_SIZE 1024


void ClientHandler(Server &server, int socket_fd, int id);


#endif //SIMPLECHAT_CLIENTHANDLER_H
