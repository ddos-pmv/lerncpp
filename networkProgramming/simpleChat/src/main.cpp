#include "headers/Server.h"

#define PORT 8080


int main(){
    try{
        Server server(PORT);
        server.start();
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}