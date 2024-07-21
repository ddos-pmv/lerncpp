#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>

int main(){
    struct sockaddr_in server_addr;
    int s;
    int rc;
    char buff[1024] = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(7500);

    s = socket( AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        std::cerr << "error system call socket";
        exit(1);
    }

    rc = connect(s,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if(rc){
        std::cerr << "error connecting with server";
        exit(1);
    }
    const char *msg = "Hi, from client!";
    rc = send(s, msg, strlen(msg), 0);
    if(rc<=0){
        std::cerr << "error, sending msg";
        exit(1);
    }

    return 0;
}
