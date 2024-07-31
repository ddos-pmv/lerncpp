//
// Created by sergey on 31.07.24.
//

#ifndef SIMPLECHAT_SERVER_H
#define SIMPLECHAT_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>
#include <mutex>
#include <vector>
#include <string>
#include <thread>
#include <list>


class Server {
public:
    Server(unsigned int port);
    void start();
private:
    int s;
    int connections = 0;

    void broadCast(std::string message);
    void removeClient(int socket_fd);

    unsigned int port;
    std::mutex clients_mutex;

    std::list<std::pair<int,int>> clients;
    std::vector<std::thread> clients_thread;

    friend void ClientHandler(Server &server, int socket_fd, int client_id);


};


#endif //SIMPLECHAT_SERVER_H
