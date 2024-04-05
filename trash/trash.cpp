#include <iostream>
#include <string>
#include <fstream>

int main(){
    std::ifstream fin;
    std::string path = "file.txt"; 
    fin.exceptions(std::fstream::badbit | std::fstream::failbit);

    try{
        fin.open(path);
        std::cout<<"File was successfully opened\n";
    }
    catch(const std::exception & ex){
        std::cout<<ex.what()<<std::endl;
        std::cout<<"FILE OPENNING error\n";
    }


    return 0;
}
