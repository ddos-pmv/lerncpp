#include "headers/Server.h"
#include "headers/ClientHandler.h"
#include <sys/socket.h>
#include <arpa/inet.h>

Server::Server(unsigned int port):port(port) {
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) throw std::runtime_error("Error system call socket");

    struct sockaddr_in local;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int opt = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
        throw std::runtime_error("Error setting options");
    }

    if (bind(s, reinterpret_cast<struct sockaddr *>(&local), sizeof(local)) < 0) {
        throw std::runtime_error("Error socket binding");
    }

    if(listen(s, 10) < 0){
        throw std::runtime_error("Error listening socket");
    }

}

void Server::start() {
    while(true){
        struct sockaddr_in client_socket_info;
        socklen_t sizeOfStruct = sizeof(client_socket_info);
        int client_socket = accept(s, reinterpret_cast<struct sockaddr*>(&client_socket_info), &sizeOfStruct);

        if(client_socket>=0){
            std::mutex tmp_mutex;
            tmp_mutex.lock();
            char client_address[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_socket_info.sin_addr, client_address, INET_ADDRSTRLEN);

            std::cout << "Connected client:" << std::endl;
            std::cout << "IP: " << client_address << std::endl;
            std::cout << "PORT: " << ntohs(client_socket_info.sin_port) << std::endl;
            std::cout << std::endl;
            tmp_mutex.unlock();


            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.push_back({++connections, client_socket});
            clients_thread.emplace_back([this, client_socket](){
                ClientHandler(*this, client_socket,connections);
            });
        }
    }
}

void Server::broadCast(std::string message) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for(auto client : clients){
        if(client.second != -1){
            int rc = send(client.second,message.c_str(), message.length()*sizeof(char), 0);
        }
    }
}

void Server::removeClient(int socket_fd) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    auto it = clients.begin();
    while(it!=clients.end()){
        if((*it).second == socket_fd){
            it = clients.erase(it);
        }
        else it++;
    }
}
