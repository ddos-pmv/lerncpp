#include "headers/ClientHandler.h"

void ClientHandler(Server &server, int socket_fd, int id){
    char buffer[BUFFER_SIZE] = {'\0'};
    while(true){
        int rc = recv(socket_fd, buffer, BUFFER_SIZE*sizeof(char),0);
        buffer[rc] = '\0';
        if(rc > 0){
            std::string message(std::to_string(id)+": "+buffer);
            server.broadCast(message);
        }
        else{
            server.removeClient(socket_fd);
            break;
        }
    }
}