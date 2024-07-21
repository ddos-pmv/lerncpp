#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h> // для close
#include <cstdlib>  // для exit

int main() {
    int s;
    int s1;
    int rc;
    struct sockaddr_in local;
    char buf[1024] = {'\0'};

    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_family = AF_INET;
    local.sin_port = htons(7500);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        std::cerr << "Error, system call socket: " << strerror(errno) << std::endl;
        exit(1);
    }

    int opt = 1;
    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0 ){
        std::cerr << "Error setting socket options: " << strerror(errno) << std::endl;
        close(s);
        exit(1);
    }

    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if (rc < 0) {
        std::cerr << "Error binding socket to local address: " << strerror(errno) << std::endl;
        close(s);
        exit(1);
    }

    rc = listen(s, 5);
    std::cout << "End of listening\n";
    if (rc < 0) {
        std::cerr << "Listen error: " << strerror(errno) << std::endl;
        close(s);
        exit(1);
    }

    s1 = accept(s, NULL, NULL);
    if (s1 < 0) {
        std::cerr << "Accepting error: " << strerror(errno) << std::endl;
        close(s);
        exit(1);
    }

    rc = recv(s1, buf, sizeof(buf), 0);
    if (rc <= 0) {
        std::cerr << "Error recv: " << strerror(errno) << std::endl;
        close(s1);
        close(s);
        exit(1);
    }

    std::cout << "Received message: " << buf << std::endl;

    close(s1);
    close(s);
    return 0;
}
