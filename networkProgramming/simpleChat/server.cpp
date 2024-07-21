#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>


#define PORT 7500

void throw_error(const std::string &msg){
    throw std::runtime_error(msg + ": " + errno);
}


int main(){
    try{
        int s;
        int rc;
        struct sockaddr_in local;

        local.sin_family = AF_INET;
        local.sin_port = htons(PORT);
        local.sin_addr.s_addr = htonl(INADDR_ANY);

        s = std::socket(AF_INET, SOCK_STREAM, 0);
        if(s < 0) thow_error("Error, system call socket");

        int opt = 1;

        if(setsockopt(s,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0){
            close(s);
            throw_error("Error setting socket options");
        }

        rc = bind(s, (struct sockaddr *)&local, sizeof(local));
        if(rc < 0){
            close(s);
            throw_error("Error binding socket to local address");
        }

        rc = listen(s,  5);
        if(rc < 0){
            close(s );
            throw_error("Error listen");
        }
        std::cout << "Server Listening now...\n";

        std::vector<std::thread> threads;
        std::atomic<bool> running(true);
        while(running)

    }
    catch (std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}