#include "../writer.hpp"

void Writer::write(const std::string &msg){
    if(msg.size() > 2 && msg.size() % 32 == 0){
        std::cout << "Data Correct" << std::endl;
    }else{
        std::cout << "Data Incorrect" << std::endl;
    }
}