#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <mutex>
#define PORT_TO_CONNECT 8080
#define BUFFER_SIZE 1024


const char *ADDR = "127.0.0.1";
std::mutex cout_mutex;


int connectToServer(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0) throw std::runtime_error("Error system call socket");

    struct sockaddr_in serverStruct;

    serverStruct.sin_family = AF_INET;
    serverStruct.sin_port = htons(PORT_TO_CONNECT);
    serverStruct.sin_addr.s_addr = inet_addr(ADDR);

    int rc = connect(s, reinterpret_cast<struct sockaddr*>(&serverStruct), sizeof(serverStruct));
    if(rc < 0){
        throw  std::runtime_error("Error connecting to server socket");
    }

    return s;
}

void receiver(int socket_fd) {
    char buffer[BUFFER_SIZE];
    while (true) {
        int rc = recv(socket_fd, buffer, BUFFER_SIZE - 1, 0);  // Оставляем место для '\0'
        if (rc <= 0) {
            std::cerr << "Error receiving msg or connection closed" << std::endl;
            break;
        }
        buffer[rc] = '\0';
        std::string strToCout(buffer);
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << strToCout << std::endl;
    }
}

void sendMessages(int socket_fd){
    std::string msg;
    while(true){
        std::getline(std::cin, msg);
        int rc = send(socket_fd, msg.c_str(), msg.size(), 0);
        if(rc <= 0){
            throw std::runtime_error("Error sending");
        }
    }
}

int main(){
    try{
       int socket_fd = connectToServer();
       std::thread receiverThread(receiver, socket_fd);
       sendMessages(socket_fd);
       receiverThread.join();
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}